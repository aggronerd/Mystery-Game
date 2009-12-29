/*
 * Overlay.cpp
 *
 *  Created on: 12 Dec 2009
 *      Author: greg
 */

#include "Overlay.h"

Overlay::Overlay(Game* game)
{
  g = game;
}

Overlay::~Overlay()
{
  g = NULL;
}
