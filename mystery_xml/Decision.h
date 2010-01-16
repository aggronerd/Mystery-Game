/*
 * Desision.h
 *
 *  Created on: 15 Jan 2010
 *      Author: greg
 */

#ifndef DECISION_H_
#define DECISION_H_

#include <ClanLib/core.h>

class Decision
{
public:
  Decision(const CL_DomElement&);
  virtual ~Decision();
private:
  CL_String name;
};

#endif /* DECISION_H_ */
