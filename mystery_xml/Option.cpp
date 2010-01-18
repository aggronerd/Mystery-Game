/*
 * Option.cpp
 *
 *  Created on: 16 Jan 2010
 *      Author: greg
 */

#include "Option.h"
#include "../logging.h"

Option::Option(const CL_DomElement& element)
{
  DEBUG_MSG("Option::Option(const CL_DomElement&) - Called.")

  CL_String ns_plot = "http://www.gregorydoran.co.uk/plot";

  //Reset Decisions object pointer to NULL.
  decisions = 0x0;

  //Parse children:
  DEBUG_MSG(CL_String("Option::Option(const CL_DomElement&) - Processing children."));
  CL_DomNode cur = element.get_first_child();
  while (!cur.is_null())
  {
    if (cur.get_namespace_uri() == ns_plot && cur.get_node_name() == "decisions")
    {
      //Delegate parsing of decision element to the Decision class:
      CL_DomElement element = cur.to_element();
      decisions = new Decisions(element);
    }
    cur = cur.get_next_sibling();
  }

}

Option::~Option()
{
  DEBUG_MSG("Option::~Option() - Called.")
  if(decisions != 0x0)
    delete decisions;
}
