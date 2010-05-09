/*
 * HotelGroundFloor.h
 *
 *  Created on: 9 May 2010
 *      Author: greg
 */

#ifndef HOTELGROUNDFLOOR_H_
#define HOTELGROUNDFLOOR_H_

#include "../GameObject.h"
#include <ClanLib/core.h>

class Scene;

class HotelGroundFloor : public GameObject {
public:
	HotelGroundFloor(Scene*, CL_Pointd&, CL_Angle&);
	virtual ~HotelGroundFloor();
	bool update(unsigned int);
};

#endif /* HOTELGROUNDFLOOR_H_ */
