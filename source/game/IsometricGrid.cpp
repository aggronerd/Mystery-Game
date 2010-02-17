/**
 * @file IsometricGrid.cpp
 *
 *  Created on: 12 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "IsometricGrid.h"
#include "IsometricConversions.h"
#include "World.h"
#include <ClanLib/core.h>

IsometricGrid::IsometricGrid(World* w) : Overlay(w)
{}

IsometricGrid::~IsometricGrid()
{}

void IsometricGrid::draw()
{
  //Get the graphic context
  CL_GraphicContext* gc = world->get_gc();
  //Create isometric grid
  for(signed int x=-30;x<=30;x++)
  {
    for(signed int y=-30;y<=30;y++)
    {
      //Draw square
      CL_Draw::line(*gc, IsometricConversions::world_to_isometric(CL_Pointf(x,y)),   IsometricConversions::world_to_isometric(CL_Pointf(x  ,y+1)), CL_Colorf(0.2f, 0.2f, 0.2f));
      CL_Draw::line(*gc, IsometricConversions::world_to_isometric(CL_Pointf(x,y)),   IsometricConversions::world_to_isometric(CL_Pointf(x+1,y  )), CL_Colorf(0.2f, 0.2f, 0.2f));
      CL_Draw::line(*gc, IsometricConversions::world_to_isometric(CL_Pointf(x+1,y)), IsometricConversions::world_to_isometric(CL_Pointf(x+1,y+1)), CL_Colorf(0.2f, 0.2f, 0.2f));
      CL_Draw::line(*gc, IsometricConversions::world_to_isometric(CL_Pointf(x,y+1)), IsometricConversions::world_to_isometric(CL_Pointf(x+1,y+1)), CL_Colorf(0.2f, 0.2f, 0.2f));
    }
  }
}
