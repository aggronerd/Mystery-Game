/*
 * vec2icomp.h
 *
 *  Created on: 24 Jul 2010
 *      Author: greg
 */

#ifndef VEC2ICOMP_H_
#define VEC2ICOMP_H_

/**
 * Structure used to compare vectors in the
 * map used to store tiles. Determines ordering
 * in the two dimensions used in an isometric
 * system.
 */
struct vec2icomp
{
  bool operator() (const CL_Vec2i& lhs, const CL_Vec2i& rhs) const
  {
  	if(lhs.y < rhs.y)
			return(true);
  	if(lhs.x < rhs.x && lhs.y == rhs.y)
 			return(true);
  	return(false);
  }
};

#endif /* VEC2ICOMP_H_ */
