/*
 * Option.h
 *
 *  Created on: 16 Jan 2010
 *      Author: greg
 */

#ifndef OPTION_H_
#define OPTION_H_

#include <ClanLib/core.h>

class Decisions;
class Plot;

class Option
{
public:
  Option(Plot*, const CL_DomElement&);
  virtual ~Option();
  int getId(void);
private:
  Decisions* decisions;
  CL_String name;
  int id;
  Plot* plot;
};

#endif /* OPTION_H_ */
