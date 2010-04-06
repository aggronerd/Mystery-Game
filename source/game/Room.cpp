/**
 * @file Room.cpp
 *
 * Created on: 4 Apr 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "Room.h"
#include "World.h"
#include <ClanLib/core.h>

Room::Room(World* w) : Overlay(w)
{
  corners.push_back(CL_Pointd(5,5));
  corners.push_back(CL_Pointd(-2,5));
  corners.push_back(CL_Pointd(-2,-5));
  corners.push_back(CL_Pointd(5,-5));
}

Room::~Room()
{
  world = 0x0;
}

void Room::draw()
{

  CL_PrimitivesArray poly(*(world->get_gc()));

  std::vector<CL_Pointd>::iterator it_corner;
  int n = 0;
  for(it_corner = corners.begin(); it_corner != corners.end(); ++it_corner)
  {
    //poly.set_attribute(n,static_cast<CL_Vec2i>(world->get_active_viewport()->get_screen_position(*it_corner)));
    n++;
  }
  //world->get_gc()->get_polygon_rasterizer().set_face_fill_mode_front(cl_fill_polygon);
  //world->get_gc()->draw_primitives(cl_polygon,n,poly);

}
