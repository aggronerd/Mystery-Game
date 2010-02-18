/**
 * @file Desision.h
 *
 *  Created on: 15 Jan 2010
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef DECISION_H_
#define DECISION_H_

#include <ClanLib/core.h>
#include "Options.h"

class Plot;

class Decision
{
public:
  Decision(Plot*, const CL_DomElement&);
  Decision(Plot*);
  virtual ~Decision();
  CL_String get_result_as_string(void);
  int get_result_as_integer(void);
  double get_result_as_double(void);
  CL_String get_result_type(void);
private:
  CL_String name;
  CL_String type;
  Options* options;
  Plot* plot;
  int* value;
  bool resolve(void);
};

#endif /* DECISION_H_ */
