/*
 * Desision.h
 *
 *  Created on: 15 Jan 2010
 *      Author: greg
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
private:
  CL_String name;
  Options* options;
  Plot* plot;
};

#endif /* DECISION_H_ */
