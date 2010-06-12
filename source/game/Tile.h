/*
 * Tile.h
 *
 *  Created on: 12 Jun 2010
 *      Author: greg
 */

#ifndef TILE_H_
#define TILE_H_

/**
 * Scene tile.
 */
class Tile
{
	public:
		Tile();
		virtual	~Tile();

	private:
		bool is_obstacle;
		CL_Sprite sprite;

};

#endif /* TILE_H_ */
