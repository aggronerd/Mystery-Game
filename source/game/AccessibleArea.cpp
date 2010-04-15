/**
 * @file AccessibleArea.cpp
 *
 * Created on: 6 Apr 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "AccessibleArea.h"
#include "Scene.h"
#include "World.h"
#include "../misc/logging.h"

AccessibleArea::AccessibleArea(Scene* owner) : scene(owner)
{
  DEBUG_MSG("AccessibleArea::AccessibleArea(Scene*) - Called.")

  points.push_back(CL_Pointd(-5,-5));
  points.push_back(CL_Pointd( 5,-5));
  points.push_back(CL_Pointd( 5, 5));
  points.push_back(CL_Pointd(-5, 5));
}

AccessibleArea::~AccessibleArea()
{
  DEBUG_MSG("AccessibleArea::~AccessibleArea() - Called.")
}

void AccessibleArea::draw()
{
  CL_GraphicContext gc = *(scene->get_world()->get_gc());
  CL_Vec2i points_array[4];

  std::list<CL_Pointd>::iterator it_point;
  int n = 0;
  for(it_point = points.begin(); it_point != points.end(); ++it_point)
  {
    points_array[n] = static_cast<CL_Vec2i>(scene->get_active_viewport()->get_screen_position(*(it_point)));
    n++;
  }

  CL_PrimitivesArray poly(gc);
  //poly.set_attribute(0, &points_array[0], n);

  //world->get_gc()->get_polygon_rasterizer().set_face_fill_mode_front(cl_fill_polygon);

  gc.draw_primitives(cl_polygon,n,poly);

}
