/*
 * NavigationMesh.h
 *
 *  Created on: 25 Jul 2010
 *      Author: greg
 */

#ifndef NAVIGATIONMESH_H_
#define NAVIGATIONMESH_H_

#include <vector>
#include "Polygon.h"

class NavigationMesh
{

	public:

		NavigationMesh();
		virtual	~NavigationMesh();
		void draw(void);

	private:

		std::vector<Polygon> _collision_polygons;

};

#endif /* NAVIGATIONMESH_H_ */
