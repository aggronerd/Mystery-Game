/**
 * @file BBN_Exception.h
 *
 * Created on: 18 Apr 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef BBN_EXCEPTION_H_
#define BBN_EXCEPTION_H_

#include <ClanLib/core.h>

class BBN_Exception : CL_Exception
{
public:
  BBN_Exception(const CL_String & message) : CL_Exception(message) {};
};

#endif /* BBN_EXCEPTION_H_ */
