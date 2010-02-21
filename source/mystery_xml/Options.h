/**
 * @file Options.h
 *
 *  Created on: 16 Jan 2010
 *      @author Gregory Doran <www.gregorydoran.co.uk>
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
  Options(Plot*);
  Options(Plot*, const CL_DomElement&);
  virtual ~Options();
  Result select(void);
  void add_option(Option* option);
private:
  std::list<Option*> options;
  Plot* plot;
  void interpret_range(CL_String);
};

#endif /* OPTIONS_H_ */
