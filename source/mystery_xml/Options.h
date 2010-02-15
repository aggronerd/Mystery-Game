/*
 * Options.h
 *
 *  Created on: 16 Jan 2010
 *      Author: greg
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <ClanLib/core.h>
#include <list>
#include "Option.h"

class Result;
class Plot;

class Options
{
public:
  Options(Plot*, const CL_DomElement&);
  virtual ~Options();
  Result select(void);
private:
  std::list<Option*> options;
  Plot* plot;
  void interpretRange(CL_String);
};

#endif /* OPTIONS_H_ */