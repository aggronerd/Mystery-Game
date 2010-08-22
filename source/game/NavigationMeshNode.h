/*
 * NavigationMeshNode.h
 *
 *  Created on: 25 Jul 2010
 *      Author: greg
 */

#ifndef NAVIGATIONMESHNODE_H_
#define NAVIGATIONMESHNODE_H_

#include "Polygon.h"
#include <vector>

class NavigationMeshNode : public Polygon
{
	public:

		NavigationMeshNode();
		virtual	~NavigationMeshNode();

	private:

		std::vector<NavigationMeshNode*> _neighbours;

};

#endif /* NAVIGATIONMESHNODE_H_ */
