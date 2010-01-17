/*
 * Decisions.h
 *
 *  Created on: 16 Jan 2010
 *      Author: greg
 */

#ifndef DECISIONS_H_
#define DECISIONS_H_

#include <list>
#include <ClanLib/core.h>

class Decision;

class Decisions
{
public:
  Decisions(const CL_DomElement&);
  virtual ~Decisions();
private:
  std::list<Decision*> decisions;
};

#endif /* DECISIONS_H_ */
