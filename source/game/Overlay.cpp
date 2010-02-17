/**
 * @file Overlay.cpp
 *
 *  Created on: 12 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "Overlay.h"

Overlay::Overlay(World* w)
{
  world = w;
}

Overlay::~Overlay()
{
  world = 0;
}
