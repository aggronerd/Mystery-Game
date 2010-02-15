/*
 * Decisions.h
 *
 *  Created on: 16 Jan 2010
 *      Author: greg
 */

#ifndef DECISIONS_H_
#define DECISIONS_H_

#include <ClanLib/core.h>
#include <list>
#include "Decision.h"

class Plot;

class Decisions
{
public:
  Decisions(Plot*, const CL_DomElement&);
  virtual ~Decisions();
private:
  std::list<Decision*> decisions;
  Plot* plot;
};

#endif /* DECISIONS_H_ */
