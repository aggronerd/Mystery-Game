/*
 * IsometricConversions.cpp
 *
 *  Created on: 12 Dec 2009
 *      Author: greg
 */

#include "IsometricConversions.h"

IsometricConversions::IsometricConversions()
{}

IsometricConversions::~IsometricConversions()
{}

CL_Pointf IsometricConversions::worldToIsometric(CL_Pointf point)
{
        CL_Pointf transformed;
        //Rotate 45 degrees.
        transformed = point.rotate(CL_Pointf(0,0),CL_Angle(45,cl_degrees));
        //Scale units
        transformed *= CL_Pointf(32,16);
        //Move across
        transformed += CL_Pointf(512,382);
        return(transformed);
}
