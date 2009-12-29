/*
 * IsometricGrid.h
 *
 *  Created on: 12 Dec 2009
 *      Author: greg
 */

#ifndef ISOMETRICGRID_H_
#define ISOMETRICGRID_H_

#include "Overlay.h"

class IsometricConversions;
class World;

/**
 * Constructs a very basic 60x60 isometric grid
 * overlay when calling the draw() function.
 */
class IsometricGrid : public Overlay
{
public:
  IsometricGrid(World*);
  virtual ~IsometricGrid();
  void draw(void);
};

#endif /* ISOMETRICGRID_H_ */
