/**
 * @file IsometricGrid.cpp
 *
 *  Created on: 12 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "IsometricGrid.h"
#include "World.h"

IsometricGrid::IsometricGrid(World* w) : Overlay(w)
{
    //Setup fonts for axis labels.
    desc.set_typeface_name("Tahoma");
    desc.set_anti_alias(true);
    desc.set_height(20);
    system_font = CL_Font_System(*(w->get_gc()), desc);
}

IsometricGrid::~IsometricGrid()
{}

void IsometricGrid::draw()
{
  //Get the graphic context
  CL_GraphicContext* gc = world->get_gc();
  //Create isometric grid
  for(signed int x=-30;x<30;x++)
  {
    for(signed int y=-30;y<30;y++)
    {
      //Draw square
      CL_Draw::line(*gc, static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd(x,y))),
                         static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd(x  ,y+1))), CL_Colorf(0.2f, 0.2f, 0.2f));
      CL_Draw::line(*gc, static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd(x,y))),
                         static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd(x+1,y  ))), CL_Colorf(0.2f, 0.2f, 0.2f));
      CL_Draw::line(*gc, static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd(x+1,y))),
                         static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd(x+1,y+1))), CL_Colorf(0.2f, 0.2f, 0.2f));
      CL_Draw::line(*gc, static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd(x,y+1))),
                         static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd(x+1,y+1))), CL_Colorf(0.2f, 0.2f, 0.2f));
    }
  }

  //Draw coloured axis lines
  CL_Draw::line(*gc, static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd( 30 , 0))),
                     static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd(-30 , 0))), CL_Colorf(1.0f,0.0f,0.0f));
  CL_Draw::line(*gc, static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd( 0,-30))),
                     static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd( 0, 30))), CL_Colorf(0.0f,1.0f,0.0f));

  //Draw axis labels
  system_font.draw_text(*gc, static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd( 30 , 0))), "(30,0)", CL_Colorf(1.0f,0.0f,0.0f));
  system_font.draw_text(*gc, static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd( 32.5 , 0))), "East", CL_Colorf(1.0f,0.0f,0.0f));
  system_font.draw_text(*gc, static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd(-30 , 0))), "(-30,0)", CL_Colorf(1.0f,0.0f,0.0f));
  system_font.draw_text(*gc, static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd(-32.5 , 0))), "West", CL_Colorf(1.0f,0.0f,0.0f));
  system_font.draw_text(*gc, static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd(  0, 30))), "(0,30)", CL_Colorf(0.0f,1.0f,0.0f));
  system_font.draw_text(*gc, static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd(  0, 32.5))), "North", CL_Colorf(0.0f,1.0f,0.0f));
  system_font.draw_text(*gc, static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd(  0,-30))), "(0,-30)", CL_Colorf(0.0f,1.0f,0.0f));
  system_font.draw_text(*gc, static_cast<CL_Pointf>(world->get_active_viewport()->get_screen_position(CL_Pointd(  0,-32.5))), "South", CL_Colorf(0.0f,1.0f,0.0f));
}
