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
    static CL_Pointf worldToIsometric(CL_Pointf);
    static CL_Pointd worldToIsometric(CL_Pointd);
    static CL_Pointd isometricToWorld(CL_Pointd);
};

#endif /* ISOMETRICCONVERSIONS_H_ */
