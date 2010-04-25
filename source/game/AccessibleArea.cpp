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

AccessibleArea::AccessibleArea(Scene* owner, double north, double east, double south, double west) : scene(owner)
{
  DEBUG_MSG("AccessibleArea::AccessibleArea(Scene*) - Called.")

  points.push_back(CL_Pointd(north,east));
  points.push_back(CL_Pointd(south,east));
  points.push_back(CL_Pointd(south,west));
  points.push_back(CL_Pointd(north,west));
}

AccessibleArea::~AccessibleArea()
{
  DEBUG_MSG("AccessibleArea::~AccessibleArea() - Called.")
  scene = 0x0;
}

void AccessibleArea::draw()
{

}
