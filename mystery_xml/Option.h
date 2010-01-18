/*
 * Option.h
 *
 *  Created on: 16 Jan 2010
 *      Author: greg
 */

#ifndef OPTION_H_
#define OPTION_H_

#include <ClanLib/core.h>
#include "Decisions.h"

class Option
{
public:
  Option(const CL_DomElement&);
  virtual ~Option();
private:
  Decisions* decisions;
};

#endif /* OPTION_H_ */
