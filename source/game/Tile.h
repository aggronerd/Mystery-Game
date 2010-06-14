/*
 * Tile.h
 *
 *  Created on: 12 Jun 2010
 *      Author: greg
 */

#ifndef TILE_H_
#define TILE_H_

#include <ClanLib/display.h>

/**
 * Scene tile.
 */
class Tile
{
	public:
		Tile(const CL_Image&);
		virtual	~Tile();
		bool get_is_obstacle(void);
		void set_is_obstacle(bool);
		CL_Image* get_image(void);

	private:
		bool _is_obstacle;
		CL_Image _image;

};

#endif /* TILE_H_ */
