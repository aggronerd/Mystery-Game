/**
 * @file IsometricConversions.cpp
 *
 *  Created on: 12 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "IsometricConversions.h"

IsometricConversions::IsometricConversions()
{}

IsometricConversions::~IsometricConversions()
{}

CL_Pointf IsometricConversions::world_to_isometric(CL_Pointf point)
{
  CL_Pointf transformed;
  //Rotate 45 degrees clockwise.
  transformed = point.rotate(CL_Pointf(0,0),CL_Angle(45,cl_degrees));
  //Scale units
  transformed *= CL_Pointf(32,16);
  //Move across
  transformed += CL_Pointf(512,382);
  return(transformed);
}

CL_Pointd IsometricConversions::world_to_isometric(CL_Pointd point)
{
  CL_Pointd transformed;
  //Rotate 45 degrees clockwise.
  transformed = point.rotate(CL_Pointd(0,0),CL_Angle(45,cl_degrees));
  //Scale units
  transformed *= CL_Pointd(32,16);
  //Move across
  transformed += CL_Pointd(512,382);
  return(transformed);
}

CL_Pointd IsometricConversions::isometric_to_world(CL_Pointd point)
{
  CL_Pointd transformed;
  //Move across
  transformed -= CL_Pointd(512,382);
  //Scale units
  transformed /= CL_Pointd(32,16);
  //Rotate 45 degrees anti-clockwise.
  transformed = point.rotate(CL_Pointd(0,0),CL_Angle(-45,cl_degrees));
  return(transformed);
}
