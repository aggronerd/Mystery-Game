/**
 * @file Decisions.h
 *
 *  Created on: 16 Jan 2010
 *      @author Gregory Doran <www.gregorydoran.co.uk>
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
  Decisions(Plot*);
  virtual ~Decisions();
  void add_decision(Decision*);
  void add_decision(void);
private:
  std::list<Decision*> decisions;
  Plot* plot;
};

#endif /* DECISIONS_H_ */
