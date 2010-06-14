/*
 * Tile.cpp
 *
 *  Created on: 12 Jun 2010
 *      Author: greg
 */

#include "Tile.h"
#include "../misc/logging.h"

Tile::Tile(const CL_Image& image)
{
	DEBUG_MSG("Tile::Tile(const CL_Image&) - Called.")

	_image = image;
	_is_obstacle = false;
}

Tile::~Tile()
{
	DEBUG_MSG("Tile::~Tile() - Called.")
}

bool Tile::get_is_obstacle()
{
	return(_is_obstacle);
}

void Tile::set_is_obstacle(bool value)
{
	_is_obstacle = value;
}

CL_Image* Tile::get_image()
{
	return(&_image);
}
