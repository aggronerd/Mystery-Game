/**
 * @file Viewport.cpp
 *
 * Created on: 31 Mar 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "Viewport.h"
#include "World.h"
#include <math.h>
#include "../misc/logging.h"

Viewport::Viewport(World* owner) : origin(0,0)
{
  world = owner;

  //Get the center of the screen.
  screen_center.x = world->get_gc()->get_width() / 2;
  screen_center.y = world->get_gc()->get_height() / 2;

  enable_scrolling = true;
  scroll_w = false;
  scroll_e = false;
  scroll_s = false;
  scroll_n = false;
}

Viewport::~Viewport()
{
  world = 0x0;
}

/**
 * Calculates and returns the position of the world CL_Pointd on the screen.
 */
CL_Point Viewport::get_screen_position(const CL_Pointd& world_position)
{
  CL_Point result;
  CL_Pointd p = world_position;

  //Subtract the position of the origin
  p = p - origin;

  //Apply unit scaling - ie sized grid
  p = p * VIEWPOINT_ZOOM;

  //Flip along both axis
  //p.y = 0 - p.y;
  p.x = 0 - p.x;

  //Rotate on (0,0) 45 degrees anti clockwise
  p.rotate(CL_Vec2<double>(0,0), CL_Angle(135, cl_degrees));

  //Scale by 0.5 along the y axis to give the illusion of depth
  p.y = p.y * VIEWPOINT_Y_SCALE;

  //Round off to the nearest integer
  result.x = static_cast<int>(round(p.x));
  result.y = static_cast<int>(round(p.y));

  //Translate to match screen origin lying in the middle of the graphic's context
  result = result + screen_center;

  return(result);
}

/**
 * Calculates and returns the position of the screen CL_Point in the world system.
 */
CL_Pointd Viewport::get_world_position(const CL_Point& screen_position)
{
  CL_Pointd result;

  //Convert to double
  result.x = static_cast<double>(round(screen_position.x));
  result.y = static_cast<double>(round(screen_position.y));

  result = result - screen_center;

  //Scale by 2 along the y axis
  result.y = result.y / VIEWPOINT_Y_SCALE;

  //Rotate on the origin (0,0) 45 clockwise
  result.rotate(CL_Vec2<double>(0,0), CL_Angle(-135, cl_degrees));

  //Flip along both axis
  //result.y = 0 - result.y;
  result.x = 0 - result.x;

  result = result / VIEWPOINT_ZOOM;

  //5. add the position of the origin in world system.
  result = result + origin;

  return(result);
}

/**
 * Calculates and determines whether a world point is visible on the screen.
 */
bool Viewport::get_is_visible(const CL_Pointd& point)
{
  //TODO: Currently off-screen sprites are still rendered.
  return(true);
}

/**
 * Changes the origin so that the viewpoint is centered on point.
 */
void Viewport::center_on_world(const CL_Pointd& point)
{

  //Subtract each from the central point to get the new origin.
  origin = point;

}

/**
 * Updates the origin to enable steady scrolling.
 */
void Viewport::update(unsigned int time_elapsed_ms)
{
  if (enable_scrolling)
  {
    double distance;
    CL_Pointd scroll_translation;
    if(scroll_w)
    {
      distance = ((static_cast<double>(time_elapsed_ms)) / 1000)
          * VIEWPOINT_SCROLL_DISTANCE_PER_SEC;
      scroll_translation.x -= distance;
      scroll_translation.y += distance;
      DEBUG_MSG("Scroll west called.")
    }
    if(scroll_n)
    {
      distance = ((static_cast<double>(time_elapsed_ms)) / 1000)
          * VIEWPOINT_SCROLL_DISTANCE_PER_SEC;
      scroll_translation.x += distance;
      scroll_translation.y += distance;
      DEBUG_MSG("Scroll north called.")
    }
    if(scroll_e)
    {
      distance = ((static_cast<double>(time_elapsed_ms)) / 1000)
          * VIEWPOINT_SCROLL_DISTANCE_PER_SEC;
      scroll_translation.x += distance;
      scroll_translation.y -= distance;
      DEBUG_MSG("Scroll east called.")
    }
    if(scroll_s)
    {
      distance = ((static_cast<double>(time_elapsed_ms)) / 1000)
          * VIEWPOINT_SCROLL_DISTANCE_PER_SEC;
      scroll_translation.x -= distance;
      scroll_translation.y -= distance;
      DEBUG_MSG("Scroll south called.")
    }
    origin += scroll_translation;
  }
}

void Viewport::set_scroll_w(bool value)
{
  scroll_w = value;
}

void Viewport::set_scroll_e(bool value)
{
  scroll_e = value;
}

void Viewport::set_scroll_s(bool value)
{
  scroll_s = value;
}

void Viewport::set_scroll_n(bool value)
{
  scroll_n = value;
}

void Viewport::set_enable_scrolling(bool value)
{
  enable_scrolling = value;
}
