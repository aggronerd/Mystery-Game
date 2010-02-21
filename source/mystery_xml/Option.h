/**
 * @file Option.h
 *
 *  Created on: 16 Jan 2010
 *      @author Gregory Doran <www.gregorydoran.co.uk>
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
  Option(Plot*);
  virtual ~Option();
  int get_id(void);
private:
  Decisions* decisions;
  CL_String name;
  float probability;
  int id;
  Plot* plot;
};

#endif /* OPTION_H_ */
