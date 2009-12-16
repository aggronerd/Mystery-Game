/*
 * IsometricGrid.cpp
 *
 *  Created on: 12 Dec 2009
 *      Author: greg
 */

#include "IsometricGrid.h"
#include "IsometricConversions.h"
#include "Game.h"
#include <ClanLib/display.h>

IsometricGrid::IsometricGrid(Game* game) : Overlay(game)
{}

IsometricGrid::~IsometricGrid()
{
}

void IsometricGrid::draw()
{
  //Get the graphic context
  CL_GraphicContext* gc = g->getGC();
  //Create isometric grid
  for(signed int x=-30;x<=30;x++)
  {
    for(signed int y=-30;y<=30;y++)
    {
      //Draw square
      CL_Draw::line(*gc, IsometricConversions::worldToIsometric(CL_Pointf(x,y)),   IsometricConversions::worldToIsometric(CL_Pointf(x  ,y+1)), CL_Colorf(1.0f, 1.0f, 1.0f));
      CL_Draw::line(*gc, IsometricConversions::worldToIsometric(CL_Pointf(x,y)),   IsometricConversions::worldToIsometric(CL_Pointf(x+1,y  )), CL_Colorf(1.0f, 1.0f, 1.0f));
      CL_Draw::line(*gc, IsometricConversions::worldToIsometric(CL_Pointf(x+1,y)), IsometricConversions::worldToIsometric(CL_Pointf(x+1,y+1)), CL_Colorf(1.0f, 1.0f, 1.0f));
      CL_Draw::line(*gc, IsometricConversions::worldToIsometric(CL_Pointf(x,y+1)), IsometricConversions::worldToIsometric(CL_Pointf(x+1,y+1)), CL_Colorf(1.0f, 1.0f, 1.0f));
    }
  }
}
