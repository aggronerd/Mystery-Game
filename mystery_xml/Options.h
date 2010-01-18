/*
 * Options.h
 *
 *  Created on: 16 Jan 2010
 *      Author: greg
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include "Option.h"
#include <list>
#include <ClanLib/core.h>

class Options
{
public:
  Options(const CL_DomElement&);
  virtual ~Options();
private:
  std::list<Option*> options;
};

#endif /* OPTIONS_H_ */
