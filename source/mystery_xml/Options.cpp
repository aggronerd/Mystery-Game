/*
 * Options.cpp
 *
 *  Created on: 16 Jan 2010
 *      Author: greg
 */

#include "Options.h"
#include "Plot.h"
#include "Result.h"
#include "../misc/logging.h"

Options::Options(Plot* p, const CL_DomElement& element) : plot(p)
{

  DEBUG_MSG("Options::Options(const CL_DomElement&) - Called.")

  //Parse children:
  DEBUG_MSG(CL_String("Options::Options(const CL_DomElement&) - Processing children."));
  CL_DomNode cur = element.get_first_child();
  while (!cur.is_null())
  {
    if (cur.get_namespace_uri() == PLOT_NS && cur.get_node_name() == "option")
    {
      //Delegate parsing of options element to the Options class:
      CL_DomElement element = cur.to_element();
      options.push_back(new Option(plot, element));
    }
    cur = cur.get_next_sibling();
  }

}

Options::~Options()
{

  DEBUG_MSG("Options::~Options() - Called.")

  // Delete all options
  std::list<Option *>::iterator it_opt;
  for(it_opt = options.begin(); it_opt != options.end(); ++it_opt)
    delete (*it_opt);
  options.clear();

}

/**
 * Picks a value based on weights and parameters.
 */
Result Options::select()
{

}