/*
 * Overlay.cpp
 *
 *  Created on: 12 Dec 2009
 *      Author: greg
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
