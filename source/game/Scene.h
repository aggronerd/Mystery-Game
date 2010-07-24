/**
 * @file Scene.h
 *
 * Created on: 5 Apr 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <list>
#include "GameObject.h"
#include "Viewport.h"
#include "Tile.h"
#include <ClanLib/core.h>
#include "vec2icomp.h"

class World;

class Scene
{
public:
  Scene(World*);
  Scene(World*, const CL_String&);
  virtual ~Scene();
  Viewport* get_active_viewport(void);
  World* get_world(void);
  void add_game_object(GameObject*);
  void draw(void);
  void update(unsigned int);
  void add_viewport(Viewport*);

private:
  std::list<Viewport*> _viewports;
  std::list<GameObject*> _game_objects;

  std::list<std::map<CL_Vec2i, int, vec2icomp >* > _layers_ordered;
  std::map<CL_String,std::map<CL_Vec2i, int, vec2icomp > > _layers; //list of layer of GIDs for tiles.
  std::map<int, CL_SharedPtr<Tile> > _tileset; //The tiles accessible by GIDs.

  World* _world;
  Viewport* _active_viewport;

  int _tile_width; //Pixels width of tile image
  int _tile_height; //Pixels height of tile image
  int _scene_width; //Width in tiles of the scene
  int _scene_height; //Height in tiles of the scene

  void load_tileset(int, int, const CL_String&, int);
  void load_tile_properties(const CL_DomElement&, int);
  void clear_tile_layer(const CL_String&);

};

#endif /* SCENE_H_ */
