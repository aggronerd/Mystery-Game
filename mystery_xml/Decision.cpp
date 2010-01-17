/*
 * Desision.cpp
 *
 *  Created on: 15 Jan 2010
 *      Author: greg
 */

#include "Decision.h"
#include "../logging.h"

Decision::Decision(const CL_DomElement& element)
{

  DEBUG_MSG("Decision::Decision(const CL_DomElement&) - Called.");

  options = 0x0;
  int options_count = 0;
  CL_String ns_plot = "http://www.gregorydoran.co.uk/plot";

  //Retrieve attributes.
  name = element.get_attribute_ns(ns_plot, "name");

  //Parse children:
  DEBUG_MSG(CL_String("Decision::Decision(const CL_DomElement&) - Processing children for '") + name + CL_String("'."));
  CL_DomNode cur = element.get_first_child();
  while (!cur.is_null())
  {
    if (cur.get_namespace_uri() == ns_plot && cur.get_node_name() == "options")
    {
      if(options_count == 0)
      {
        //Delegate parsing of options element to the Options class:
        CL_DomElement e = cur.to_element();
        options = new Options(e);
      }
      options_count++;
    }
    else if (cur.get_namespace_uri() == ns_plot && cur.get_node_name() == "english")
    {
      //TODO: Process <english> tag.
    }
    cur = cur.get_next_sibling();
  }

  //Ensure there weren't too many or too few options tags.
  if(options_count > 1)
  {
    throw CL_DomException("Too many options tags",CL_DomException::NOT_SUPPORTED_ERR);
  }
  else if(options_count < 1)
  {
    throw CL_DomException("No options element found",CL_DomException::NOT_SUPPORTED_ERR);
  }

}

Decision::~Decision()
{
  DEBUG_MSG("Decision::~Decision() - Called.");
  if(options != 0x0)
    delete options;
}
