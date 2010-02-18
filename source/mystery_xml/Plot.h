/**
 * @file Plot.h
 *
 *  Created on: 15 Jan 2010
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef PLOT_H_
#define PLOT_H_

#include <ClanLib/core.h>
#include <map>

//XML namespace used here for extra verification:
#define PLOT_NS "http://www.gregorydoran.co.uk/plot"

class Option;
class Decisions;

/**
 * The plot class is use to parse the plot element in the
 * mystery_xml library.
 */
class Plot
{
public:
  Plot(const char*);
  Plot(void);
  virtual ~Plot();
  void add_option(Option*);
  Decisions* get_root_decisions(void);
private:
  CL_String name;
  Decisions* decisions;
  std::map<int, Option*> options; //The master list of options accessed using their id.
};

#endif /* PLOT_H_ */
