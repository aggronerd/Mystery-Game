/*
 * Options.cpp
 *
 *  Created on: 16 Jan 2010
 *      Author: greg
 */

#include "Options.h"
#include "../logging.h"

Options::Options(const CL_DomElement& element)
{

  DEBUG_MSG("Options::Options(const CL_DomElement&) - Called.")

  CL_String ns_plot = "http://www.gregorydoran.co.uk/plot";

  //Parse children:
  DEBUG_MSG(CL_String("Options::Options(const CL_DomElement&) - Processing children."));
  CL_DomNode cur = element.get_first_child();
  while (!cur.is_null())
  {
    if (cur.get_namespace_uri() == ns_plot && cur.get_node_name() == "option")
    {
      //Delegate parsing of options element to the Options class:
      CL_DomElement element = cur.to_element();
      options.push_back(Option(element));
    }
    cur = cur.get_next_sibling();
  }

}

Options::~Options()
{

  DEBUG_MSG("Options::~Options() - Called.")

  // Delete all options
  //options.clear(); //TODO: Ensure clears the memory.
}
