/**
 * @file IsometricConversions.h
 *
 *  Created on: 12 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef ISOMETRICCONVERSIONS_H_
#define ISOMETRICCONVERSIONS_H_

#include <ClanLib/core.h>

class IsometricConversions
{
  public:
    IsometricConversions();
    virtual ~IsometricConversions();
    static CL_Pointf world_to_isometric(CL_Pointf);
    static CL_Pointd world_to_isometric(CL_Pointd);
    static CL_Pointd isometric_to_world(CL_Pointd);
};

#endif /* ISOMETRICCONVERSIONS_H_ */
