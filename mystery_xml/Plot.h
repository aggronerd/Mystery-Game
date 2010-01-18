/*
 * Plot.h
 *
 *  Created on: 15 Jan 2010
 *      Author: greg
 */

#ifndef PLOT_H_
#define PLOT_H_

#include <ClanLib/core.h>

class Decisions;

class Plot
{
public:
  Plot(const char*);
  virtual ~Plot();
private:
  CL_String name;
  Decisions* decisions;
};

#endif /* PLOT_H_ */
