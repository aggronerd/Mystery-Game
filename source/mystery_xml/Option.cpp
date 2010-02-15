/*
 * Option.cpp
 *
 *  Created on: 16 Jan 2010
 *      Author: greg
 */

#include "Option.h"
#include "Plot.h"
#include "../misc/logging.h"

Option::Option(Plot* p, const CL_DomElement& element) : plot(p)
{
  DEBUG_MSG("Option::Option(const CL_DomElement&) - Called.")

  //Reset Decisions object pointer to NULL.
  decisions = 0x0;

  //Store attributes.
  name = element.get_attribute("name");
  id = CL_StringHelp::text_to_int(element.get_attribute("id"),10); //TODO: test existance
  DEBUG_MSG(CL_String("Option::Option(const CL_DomElement&) - Found id=") + CL_StringHelp::int_to_text(id) + CL_String(" name='") + name + CL_String("'."))

  //Parse children:
  DEBUG_MSG(CL_String("Option::Option(const CL_DomElement&) - Processing children."));
  CL_DomNode cur = element.get_first_child();
  while (!cur.is_null())
  {
    if (cur.get_namespace_uri() == PLOT_NS && cur.get_node_name() == "decisions")
    {
      //Delegate parsing of decision element to the Decision class:
      CL_DomElement element = cur.to_element();
      decisions = new Decisions(plot, element);
    }
    cur = cur.get_next_sibling();
  }

  //Add option to plot's main index.
  plot->addOption(this);

}

Option::~Option()
{
  DEBUG_MSG("Option::~Option() - Called.")
  if(decisions != 0x0)
    delete decisions;
}

int Option::getId()
{
  return(id);
}
