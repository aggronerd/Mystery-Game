/**
 * @file Scene.cpp
 *
 * Created on: 5 Apr 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "Scene.h"
#include "World.h"
#include <list>
#include "../misc/logging.h"

/**
 * Simple version of the constructor.
 *
 * @param owner
 * @return
 */
Scene::Scene(World* owner) : _world(owner)
{
	DEBUG_MSG("Scene::Scene(World*) - Called.")

	_tile_width = 64;
	_tile_height = 128;
	_scene_height = 0;
	_scene_width = 0;

	//Set viewport to new one for configuring camera.
  _active_viewport = new Viewport(this);
  add_viewport(_active_viewport);
}

/**
 * Contructs scene from tiled level editor XML file.
 *
 * @param owner
 * @param file_name
 * @return
 */
Scene::Scene(World* owner, const CL_String& file_name) : _world(owner)
{
	DEBUG_MSG("Scene::Scene(World*, const CL_String&) - Called.")

	//Set viewport to new one for configuring camera.
	_active_viewport = new Viewport(this);
	add_viewport(_active_viewport);

	//Parse the tilesets.
	DEBUG_MSG("Opening scene '" + file_name + "'...")
	CL_File xml_file(file_name);
	CL_DomDocument document(xml_file);
	DEBUG_MSG("Successfully opened file. Parsing XML...")

	//Calculate root for relative paths.
	CL_String working_dir = CL_PathHelp::get_basepath(file_name);
	DEBUG_MSG("Working dir = '" + working_dir + "'")

	CL_DomElement root = document.get_document_element();
	_tile_width = CL_StringHelp::text_to_int(root.get_attribute("tilewidth"));
	_tile_height = CL_StringHelp::text_to_int(root.get_attribute("tileheight"));
	_scene_width = CL_StringHelp::text_to_int(root.get_attribute("width"));
	_scene_height = CL_StringHelp::text_to_int(root.get_attribute("height"));

	DEBUG_MSG("Attributes found:")
	DEBUG_MSG(CL_String("_tile_width = ") + CL_StringHelp::int_to_text(_tile_width))
	DEBUG_MSG(CL_String("_tile_height = ") + CL_StringHelp::int_to_text(_tile_height))
	DEBUG_MSG(CL_String("_scene_width = ") + CL_StringHelp::int_to_text(_scene_width))
	DEBUG_MSG(CL_String("_scene_height = ") + CL_StringHelp::int_to_text(_scene_height))

	CL_DomNode cur = root.get_first_child();
	int tile_gid;

	/*
	 * Loop through first elements.
	 */
	while (!cur.is_null())
	{
		if (cur.get_node_name() == CL_String("tileset"))
		{

			DEBUG_MSG("Found tileset.")

			CL_DomElement tileset_element = cur.to_element();

			//Load the tiles from a tileset.
			int first_gid = CL_StringHelp::text_to_int(
				tileset_element.get_attribute("firstgid"));
			int tile_width = CL_StringHelp::text_to_int(
				tileset_element.get_attribute("tilewidth"));
			int tile_height = CL_StringHelp::text_to_int(
				tileset_element.get_attribute("tileheight"));

			//Get the tileset
			CL_String tileset_filename = "";
			CL_DomNode tileset_node = tileset_element.get_first_child();
			int image_element_count = 0;

			while (!tileset_node.is_null())
			{

				if(tileset_node.get_node_name() == CL_String("image"))
				{
					//Proceed to load tileset from image.
					tileset_filename = tileset_node.to_element().get_attribute("source");

					//Append relative path of image to path of map
					tileset_filename = working_dir + tileset_filename;

					load_tileset(tile_width,tile_height,tileset_filename,first_gid);
					image_element_count ++;
				}
				else if (tileset_node.get_node_name() == CL_String("tile"))
				{
					//Cannot set properties if no image was used to load tiles from.
					if(image_element_count==0)
						throw CL_Exception("Could not find image element for tileset or does not preseed tile element.");

					//Defer to method
					CL_DomElement tile_element = tileset_node.to_element();
					load_tile_properties(tile_element, first_gid);
				}

				//Fetch next tileset definintion
				tileset_node = tileset_node.get_next_sibling();

			}

		}
		else if (cur.get_node_name() == CL_String("layer"))
		{

			DEBUG_MSG("Found layer.")

			//Get layer width and height
			CL_DomElement layer_element = cur.to_element();
			int layer_width = CL_StringHelp::text_to_int(
					layer_element.get_attribute("width"));
			//int layer_height = CL_StringHelp::text_to_int(
			//		layer_element.get_attribute("height"));
			CL_String layer_name = layer_element.get_attribute("name");

			//Zero layer
			clear_tile_layer(layer_name);

			//Order in XML is order drawn.
			_layers_ordered.push_back(&(_layers[layer_name]));

			CL_DomNode cur2 = cur.get_first_child();
			while(!cur2.is_null())
			{
				if(cur2.get_node_name()==CL_String("data"))
				{

					//Counter for current tile.
					int n = 0;
					CL_Vec2i pos;

					CL_DomNode cur3 = cur2.get_first_child();
					while(!cur3.is_null())
					{
						if(cur3.get_node_name()==CL_String("tile"))
						{

							CL_DomElement tile_element = cur3.to_element();

							//Set GID in grid
							pos.x = 0-((n / layer_width) - (_scene_width / 2));
							pos.y = 0-((n % layer_width) - (_scene_height / 2));

							tile_gid =  CL_StringHelp::text_to_int(
									tile_element.get_attribute("gid"));

							_layers[layer_name][pos] = tile_gid;

							n++;

						}
						cur3 = cur3.get_next_sibling();
					}

				}
				cur2 = cur2.get_next_sibling();
			}

		}

		cur = cur.get_next_sibling();

	}

}

/**
 *
 * Sets tile GIDs of chosen layer to 0.
 *
 * @param index
 */
void Scene::clear_tile_layer(const CL_String& name)
{
	CL_Vec2i pos;
	for(int x=0-(_scene_width/2); x<(_scene_width/2); x++)
	{
		for(int y=0-(_scene_height/2); y<(_scene_height/2); y++)
		{
			pos.x = x;
			pos.y = y;
			_layers[name][pos] = 0;
		}
	}
}

/**
 *
 * Sets tile properties based on the XML of a tile tag.
 *
 * @param element
 */
void Scene::load_tile_properties(const CL_DomElement& element, int first_gid)
{
	//Get ID
	int tile_id = CL_StringHelp::text_to_int(
			element.get_attribute("id"));

	//Load properties
	CL_DomNode cur = element.get_first_child();
	while(!cur.is_null())
	{
		if(cur.get_node_name() == CL_String("properties"))
		{
			CL_DomNode cur2 = cur.get_first_child();
			while(!cur2.is_null())
			{
				if(cur2.get_node_name() == CL_String("property"))
				{

					//Load property values.
					CL_DomElement property_element = cur2.to_element();
					CL_String property_name = property_element.get_attribute("name");

					//Parse
					if(property_name == CL_String("collision"))
					{
						_tileset[first_gid+tile_id]->set_is_obstacle(
								CL_StringHelp::text_to_bool(property_element.get_attribute("value")));
					}

				}
				cur2 = cur2.get_next_sibling();
			}
		}
		cur = cur.get_next_sibling();
	}
}

/**
 * Loads tiles from the tileset.
 *
 * @param tile_width
 * @param tile_height
 * @param filename
 * @param first_gid
 */
void Scene::load_tileset(int tile_width, int tile_height, const CL_String& filename, int first_gid)
{

	DEBUG_MSG(CL_String("Scene::load_tileset(int tile_width = ") + CL_StringHelp::int_to_text( tile_width) +
			                ", int tile_height = " + CL_StringHelp::int_to_text(tile_height) +
			                ", const CL_String& filename = '" + filename +
			                "', int first_gid = " + CL_StringHelp::int_to_text(first_gid) + ") - Called.")

	CL_Texture tileset(*(this->get_world()->get_gc()),filename);
	int grid_width = tileset.get_width() / tile_width;
	int grid_height =  tileset.get_height() / tile_height;
	int gid = first_gid;

	//Slice up the grid:
	for(int y = 0; y < grid_height; y++)
	{
		for(int x = 0; x < grid_width; x++)
		{
			CL_Rect tile_geom;
			tile_geom.left = x*tile_width;
			tile_geom.right = tile_geom.left+(tile_width);
			tile_geom.top = y*tile_height;
			tile_geom.bottom = tile_geom.top+(tile_height);

			DEBUG_MSG("Scene::load_tileset(int, int, const CL_String&, int) - Cutting out left=" +
					      CL_StringHelp::int_to_text(tile_geom.left) + ", right = " +
					      CL_StringHelp::int_to_text(tile_geom.right) + ", top = " +
					      CL_StringHelp::int_to_text(tile_geom.top) + ", bottom = " +
					      CL_StringHelp::int_to_text(tile_geom.bottom) + " for gid = " +
					      CL_StringHelp::int_to_text(gid) + ".")

			//Cut sub-texture
			//CL_Subtexture tile(tileset,tile_geom);
			CL_Image tile_tex(*(this->get_world()->get_gc()),tileset, tile_geom);
			CL_SharedPtr<Tile> tile_ptr(new Tile(tile_tex));

			_tileset[gid] = tile_ptr;

			gid++;
		}
	}
}

Scene::~Scene()
{
  DEBUG_MSG("Scene::~Scene() - Called.")

  // Delete all game objects
  std::list<GameObject *>::iterator it_go;
  for(it_go = _game_objects.begin(); it_go != _game_objects.end(); ++it_go)
    delete (*it_go);
  _game_objects.clear();

  // Delete all viewports
  std::list<Viewport *>::iterator it_vp;
  for(it_vp = _viewports.begin(); it_vp != _viewports.end(); ++it_vp)
    delete (*it_vp);
  _viewports.clear();

  _world = 0x0;
}

/**
 * Adds a game object to the scene.
 */
void Scene::add_game_object(GameObject* game_object)
{
  _game_objects.push_back(game_object);
}

/**
 * Draws all game objects etc.
 */
void Scene::draw()
{
  //TODO: determine something about depth.
	//TODO: draw only those tiles in view.

	int tile_gid = 0;

	// Draw tiles
	std::list<std::map<CL_Vec2i, int, vec2icomp>* >::iterator it_layer;
	CL_Vec2i pos;

	if(_layers_ordered.size() > 0 && _active_viewport != 0x0)
	{

		for(int y=(_scene_height/2)-1; y>=(0-(_scene_height/2)); y--)
		{
			for(int x=(_scene_width/2)-1; x>=(0-(_scene_width/2)); x--)
			{
				CL_Pointd world_point_bottom = CL_Pointd(x,y);
				CL_Pointd world_point_left = CL_Pointd(x,y+1);
				CL_Pointd world_point_right = CL_Pointd(x+1,y);
				CL_Point screen_point_bottom =
						_active_viewport->get_screen_position(world_point_bottom);
				CL_Point screen_point_left =
						_active_viewport->get_screen_position(world_point_left);
				CL_Point screen_point_right =
						_active_viewport->get_screen_position(world_point_right);

				//Tile rectangle size and position.
				CL_Rectf rec;

				rec.left = static_cast<float>(screen_point_left.x);
				rec.top = static_cast<float>(screen_point_bottom.y) - 128;
				rec.right = static_cast<float>(screen_point_right.x);
				rec.bottom = static_cast<float>(screen_point_bottom.y);

				pos.x = x;
				pos.y = y;

				//rec.top = 0;
				//rec.bottom = 63;
				//rec.left = 0;
				//rec.right = 63;

				//Iterate through layers.
				for(it_layer = _layers_ordered.begin(); it_layer != _layers_ordered.end(); ++it_layer)
				{

					tile_gid = (*(*it_layer))[pos];
					if(tile_gid > 0)
					{
						CL_Image* tile = _tileset[tile_gid]->get_image();

						tile->draw(*(this->get_world()->get_gc()), rec.left, rec.top);
					}
				}

			}
		}
	}

	// Draw all game objects
	std::list<GameObject*>::iterator it_go;
	for(it_go = _game_objects.begin(); it_go != _game_objects.end(); ++it_go)
	  (*it_go)->draw();
}

/**
 * Updates contents.
 */
void Scene::update(unsigned int time_elapsed_ms)
{
  // Update viewport
  _active_viewport->update(time_elapsed_ms);

  // Update all game objects
  std::list<GameObject*>::iterator it_go;
  for(it_go = _game_objects.begin(); it_go != _game_objects.end(); )
  {
    //If update returns false the object should be deleted.
    if((*it_go)->update(time_elapsed_ms) == false)
    {
      delete((*it_go));
      it_go = _game_objects.erase(it_go);
    }
    else
      ++it_go;
  }
}

Viewport* Scene::get_active_viewport()
{
  return(_active_viewport);
}

World* Scene::get_world()
{
  return(_world);
}

void Scene::add_viewport(Viewport* new_viewport)
{
  _viewports.push_back(new_viewport);
}

