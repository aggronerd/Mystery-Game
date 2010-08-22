/**
 * @file Scene.cpp
 *
 * Created on: 5 Apr 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "Scene.h"
#include "World.h"
#include "Polygon.h"
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
	_show_collision_map = false;

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
Scene::Scene(World* owner, const CL_String8& file_name) : _world(owner)
{
	DEBUG_MSG("Scene::Scene(World*, const CL_String8&) - Called.")

	//Set viewport to new one for configuring camera.
	_active_viewport = new Viewport(this);
	_show_collision_map = false;
	add_viewport(_active_viewport);

	//Parse the tilesets.
	DEBUG_MSG("Opening scene '" + file_name + "'...")
	CL_File xml_file(file_name);
	CL_DomDocument document(xml_file);
	DEBUG_MSG("Successfully opened file. Parsing XML...")

	//Calculate root for relative paths.
	CL_String8 working_dir = CL_PathHelp::get_basepath(file_name);
	DEBUG_MSG("Working dir = '" + working_dir + "'")

	CL_DomElement root = document.get_document_element();
	_tile_width = CL_StringHelp::text_to_int(root.get_attribute("tilewidth"));
	_tile_height = CL_StringHelp::text_to_int(root.get_attribute("tileheight"));
	_scene_width = CL_StringHelp::text_to_int(root.get_attribute("width"));
	_scene_height = CL_StringHelp::text_to_int(root.get_attribute("height"));

	DEBUG_MSG("Attributes found:")
	DEBUG_MSG(CL_String8("_tile_width = ") + CL_StringHelp::int_to_text(_tile_width))
	DEBUG_MSG(CL_String8("_tile_height = ") + CL_StringHelp::int_to_text(_tile_height))
	DEBUG_MSG(CL_String8("_scene_width = ") + CL_StringHelp::int_to_text(_scene_width))
	DEBUG_MSG(CL_String8("_scene_height = ") + CL_StringHelp::int_to_text(_scene_height))

	CL_DomNode cur = root.get_first_child();
	int tile_gid;

	/*
	 * Loop through first elements.
	 */
	while (!cur.is_null())
	{
		if (cur.get_node_name() == CL_String8("tileset"))
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
			CL_String8 tileset_filename = "";
			CL_DomNode tileset_node = tileset_element.get_first_child();
			int image_element_count = 0;

			while (!tileset_node.is_null())
			{

				if(tileset_node.get_node_name() == CL_String8("image"))
				{
					//Proceed to load tileset from image.
					tileset_filename = tileset_node.to_element().get_attribute("source");

					//Append relative path of image to path of map
					tileset_filename = working_dir + tileset_filename;

					load_tileset(tile_width,tile_height,tileset_filename,first_gid);
					image_element_count ++;
				}
				else if (tileset_node.get_node_name() == CL_String8("tile"))
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
		else if (cur.get_node_name() == CL_String8("layer"))
		{

			DEBUG_MSG("Found layer.")

			//Get layer width and height
			CL_DomElement layer_element = cur.to_element();
			int layer_width = CL_StringHelp::text_to_int(
					layer_element.get_attribute("width"));
			//int layer_height = CL_StringHelp::text_to_int(
			//		layer_element.get_attribute("height"));
			CL_String8 layer_name = layer_element.get_attribute("name");

			//Zero layer
			clear_tile_layer(layer_name);

			//Order in XML is order drawn.
			_layers_ordered.push_back(&(_layers[layer_name]));

			CL_DomNode cur2 = cur.get_first_child();
			while(!cur2.is_null())
			{
				if(cur2.get_node_name()==CL_String8("data"))
				{

					//Counter for current tile.
					int n = 0;
					CL_Vec2i pos;

					CL_DomNode cur3 = cur2.get_first_child();
					while(!cur3.is_null())
					{
						if(cur3.get_node_name()==CL_String8("tile"))
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
void Scene::clear_tile_layer(const CL_String8& name)
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
		if(cur.get_node_name() == CL_String8("properties"))
		{
			CL_DomNode cur2 = cur.get_first_child();
			while(!cur2.is_null())
			{
				if(cur2.get_node_name() == CL_String8("property"))
				{

					//Load property values.
					CL_DomElement property_element = cur2.to_element();
					CL_String8 property_name = property_element.get_attribute("name");

					//Parse
					if(property_name == CL_String8("collision"))
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
void Scene::load_tileset(int tile_width, int tile_height, const CL_String8& filename, int first_gid)
{

	DEBUG_MSG(CL_String8("Scene::load_tileset(int tile_width = ") + CL_StringHelp::int_to_text( tile_width) +
			                ", int tile_height = " + CL_StringHelp::int_to_text(tile_height) +
			                ", const CL_String8& filename = '" + filename +
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

			DEBUG_MSG("Scene::load_tileset(int, int, const CL_String8&, int) - Cutting out left=" +
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

/**
 * @return
 */
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
	//TODO: draw only those tiles in view.

	int tile_gid = 0;
	CL_GraphicContext gc = *(this->get_world()->get_gc());

	// Draw tiles
	std::list<std::map<CL_Vec2i, int, vec2icomp>* >::iterator it_layer;
	CL_Vec2i pos;

	//Ensure that firstly the active viewport exists and there
	// are layers to render.
	if(_layers_ordered.size() > 0 && _active_viewport != 0x0)
	{

		//Draw from furthest x value to nearest
		for(int y=(_scene_height/2)-1; y>=(0-(_scene_height/2)); y--)
		{

			//Draw from furthest y value to nearest
			for(int x=(_scene_width/2)-1; x>=(0-(_scene_width/2)); x--)
			{

				//Determine where to draw this tile.
				CL_Pointd world_point_bottom = CL_Pointd(x,y);
				CL_Pointd world_point_left = CL_Pointd(x,y+1);
				CL_Pointd world_point_right = CL_Pointd(x+1,y);
				CL_Point screen_point_bottom =
						_active_viewport->get_screen_position(world_point_bottom);
				CL_Point screen_point_left =
						_active_viewport->get_screen_position(world_point_left);
				CL_Point screen_point_right =
						_active_viewport->get_screen_position(world_point_right);
				bool draw_collision_marker = false;

				//Tile rectangle size and position.
				CL_Rectf rec;
				rec.left = static_cast<float>(screen_point_left.x);
				rec.top = static_cast<float>(screen_point_bottom.y) - 128;
				rec.right = static_cast<float>(screen_point_right.x);
				rec.bottom = static_cast<float>(screen_point_bottom.y);

				pos.x = x;
				pos.y = y;

				//Iterate through layers of tiles for this square.
				for(it_layer = _layers_ordered.begin(); it_layer != _layers_ordered.end(); ++it_layer)
				{

					tile_gid = (*(*it_layer))[pos];

					if(tile_gid > 0)
					{
						CL_Image* tile = _tileset[tile_gid]->get_image();

						//Draw the tile
						tile->draw(gc, rec.left, rec.top);

						//Draw red overlay if collision tile
						if(_show_collision_map)
						{

							if(_tileset[tile_gid]->get_is_obstacle())
							{

								draw_collision_marker = true;

							}

						}

					}

				}

				if(draw_collision_marker && _show_collision_map)
				{

					//If one of the tiles is a collision tile then draw.
					CL_Pointf left   = rec.get_bottom_left() + CL_Pointf(1,-17);
					CL_Pointf bottom = rec.get_bottom_left() + CL_Pointf(33, -1);
					CL_Pointf right  = rec.get_bottom_left() + CL_Pointf(65,-17);
					CL_Pointf top    = rec.get_bottom_left() + CL_Pointf(33,-33);

					Polygon tile;
					tile.add_point(left);
					tile.add_point(top);
					tile.add_point(bottom);
					tile.add_point(right);
					tile.add_point(left);
					tile.add_point(bottom);
					tile.add_point(top);
					tile.add_point(right);

					tile.set_line_color(CL_Colorf(1.0f,0.0f,0.0f,1.0f));
					tile.draw(gc);

				}

			}

		}

	}

	// Draw all game objects TODO: determine where to put them relative to the tiles.
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

/**
 *
 * @return
 */
Viewport* Scene::get_active_viewport()
{
  return(_active_viewport);
}

/**
 *
 * @return
 */
World* Scene::get_world()
{
  return(_world);
}

/**
 *
 * @param new_viewport
 */
void Scene::add_viewport(Viewport* new_viewport)
{
  _viewports.push_back(new_viewport);
}

/**
 * @param value Value defining whether to display the collision map on render.
 */
void Scene::set_show_navigation_mesh(bool value)
{
	_show_collision_map = value;
}

/**
 * @return Value defining whether to display the collision map on render.
 */
bool Scene::get_show_navigation_mesh()
{
	return(_show_collision_map);
}

/**
 * Replaces the navigation mesh used for path finding with
 * a newer version based on the tiles and whether they are
 * described as accessible.
 */
void Scene::update_navigation_mesh()
{

	CL_Vec2i pos;
	std::list<std::map<CL_Vec2i, int, vec2icomp>* >::iterator it_layer;
	std::map<CL_Vec2i, int, vec2icomp> navigation_grid;
	bool collision_tile;
	int i = 1;
	int tile_gid;

	/*
	 * Iterate through tiles to construct a 2d grid describing
	 * the accessibility of each tile. This is specified using
	 * a map with values given as booleans (true for navigatable
	 * and false for inaccessible tiles).
	 */
	for(int y=(_scene_height/2)-1; y>=(0-(_scene_height/2)); y--)
	{

		for(int x=(_scene_width/2)-1; x>=(0-(_scene_width/2)); x--)
		{

			pos.x = x;
			pos.y = y;
			collision_tile = false;

			//Iterate through layers of tiles for this square.
			for(it_layer = _layers_ordered.begin(); it_layer != _layers_ordered.end(); ++it_layer)
			{

				//Fetch the tile
				tile_gid = (*(*it_layer))[pos];
				Tile* tile = _tileset[tile_gid];

				if(tile->get_is_obstacle()) {
					collision_tile = true;
				}
			}

			//If is collision tile append to new collision grid
			if(collision_tile)
			{
				navigation_grid[pos] = 0;
			}
			else
			{

				/*
				 * The tile is a collision tile. If collision tile neighbours
				 * another then use the same number to indicate it should be
				 * part of the same polygon later in the process.
				 */
				if(navigation_grid[(pos + CL_Vec2i(-1, 0))] > 0)
				{
					navigation_grid[pos] = navigation_grid[pos + CL_Vec2i(-1, 0)];
				}
				else if(navigation_grid[pos + CL_Vec2i( 1, 0)] > 0)
				{
					navigation_grid[pos] = navigation_grid[pos + CL_Vec2i( 1, 0)];
				}
				else if(navigation_grid[pos + CL_Vec2i( 0,-1)] > 0)
				{
					navigation_grid[pos] = navigation_grid[pos + CL_Vec2i( 0,-1)];
				}
				else if(navigation_grid[pos + CL_Vec2i( 0, 1)] > 0)
				{
					navigation_grid[pos] = navigation_grid[pos + CL_Vec2i( 0, 1)];
				}
				else
				{
					navigation_grid[pos] = i;
					i++;
				}

			}

		}

	}

	//Construct polygons
	std::vector<Polygon> polygons;

	for(int j = 1; j < i; j++)
	{

		//Find the first instance of a number
		for(int y=(_scene_height/2)-1; y>=(0-(_scene_height/2)); y--)
		{

			for(int x=(_scene_width/2)-1; x>=(0-(_scene_width/2)); x--)
			{

				pos.x = x;
				pos.y = y;

				if(navigation_grid[pos] == j)
				{

					int current_direction = 0; //down


				}

			}

		}

	}

	//Pass boolean map to to the navigation mesh to construct somethin.

}
