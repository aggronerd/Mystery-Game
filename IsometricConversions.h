/*
 * IsometricConversions.h
 *
 *  Created on: 12 Dec 2009
 *      Author: greg
 */

#ifndef ISOMETRICCONVERSIONS_H_
#define ISOMETRICCONVERSIONS_H_

#include <ClanLib/core.h>

class IsometricConversions
{
  public:
    IsometricConversions();
    virtual ~IsometricConversions();
    static CL_Pointf worldToIsometric(CL_Pointf point);
};

#endif /* ISOMETRICCONVERSIONS_H_ */
