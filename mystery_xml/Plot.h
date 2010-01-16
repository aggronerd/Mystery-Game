/*
 * Plot.h
 *
 *  Created on: 15 Jan 2010
 *      Author: greg
 */

#ifndef PLOT_H_
#define PLOT_H_

#include <ClanLib/core.h>

class Plot
{
public:
  Plot(const char*);
  virtual ~Plot();
private:
  void parseXML();
  CL_File* xmlFile;
  CL_String name;
};

#endif /* PLOT_H_ */
