/**
 * @file Decisions.cpp
 *
 *  Created on: 16 Jan 2010
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "Decisions.h"
#include "Decision.h"
#include "Plot.h"
#include "../misc/logging.h"

Decisions::Decisions(Plot* p, const CL_DomElement& element) : plot(p)
{

  DEBUG_MSG("Decisions::Decisions(const CL_DomElement&) - Called.")

  //Fetch attributes
  //TODO: Add itteration & duplication.

  //Parse children:
  DEBUG_MSG(CL_String("Decisions::Decisions(const CL_DomElement&) - Processing children."));
  CL_DomNode cur = element.get_first_child();
  while (!cur.is_null())
  {
    if (cur.get_namespace_uri() == PLOT_NS && cur.get_node_name() == "decision")
    {
      //Delegate parsing of decision element to the Decision class:
      CL_DomElement element = cur.to_element();
      decisions.push_back(new Decision(plot, element));
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
