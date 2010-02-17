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
  virtual ~Decision();
  CL_String getResultAsString(void);
  int getResultAsInteger(void);
  double getResultAsDouble(void);
  CL_String getResultType(void);
private:
  CL_String name;
  CL_String type;
  Options* options;
  Plot* plot;
  int* value;
  bool resolve(void);
};

#endif /* DECISION_H_ */
