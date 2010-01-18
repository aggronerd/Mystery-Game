/*
 * Decisions.cpp
 *
 *  Created on: 16 Jan 2010
 *      Author: greg
 */

#include "Decisions.h"
#include "Decision.h"
#include "../logging.h"

Decisions::Decisions(const CL_DomElement& element)
{

  DEBUG_MSG("Decisions::Decisions(const CL_DomElement&) - Called.")

  CL_String ns_plot = "http://www.gregorydoran.co.uk/plot";

  //Fetch attributes

  //Parse children:
  DEBUG_MSG(CL_String("Decisions::Decisions(const CL_DomElement&) - Processing children."));
  CL_DomNode cur = element.get_first_child();
  while (!cur.is_null())
  {
    if (cur.get_namespace_uri() == ns_plot && cur.get_node_name() == "decision")
    {
      //Delegate parsing of decision element to the Decision class:
      CL_DomElement element = cur.to_element();
      decisions.push_back(new Decision(element));
    }
    cur = cur.get_next_sibling();
  }

}

Decisions::~Decisions()
{

  DEBUG_MSG("Decisions::~Decisions() - Called.")

  // Delete decision objects.
  std::list<Decision *>::iterator it_des;
  for(it_des = decisions.begin(); it_des != decisions.end(); ++it_des)
    delete (*it_des);
  decisions.clear();

}
