/**
 * @file Desision.cpp
 *
 *  Created on: 15 Jan 2010
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "Decision.h"
#include "Plot.h"
#include "../misc/logging.h"

Decision::Decision(Plot* p, const CL_DomElement& element) : plot(p)
{

  DEBUG_MSG("Decision::Decision(const CL_DomElement&) - Called.");

  int options_count = 0;

  //Set object pointers to NULL
  options = 0x0;
  value = 0x0;

  //Retrieve attributes.
  name = element.get_attribute_ns(PLOT_NS, "name");
  type = element.get_attribute_ns(PLOT_NS, "type");

  //Parse children:
  DEBUG_MSG(CL_String("Decision::Decision(const CL_DomElement&) - Processing children for '") + name + CL_String("' type='") + type + CL_String("'."));
  CL_DomNode cur = element.get_first_child();
  while (!cur.is_null())
  {
    //
    // <options>
    //
    if (cur.get_namespace_uri() == PLOT_NS && cur.get_node_name() == "options")
    {
      if(options_count == 0)
      {
        //Delegate parsing of options element to the Options class:
        CL_DomElement e = cur.to_element();
        options = new Options(plot, e);
      }
      options_count++;
    }
    //
    // <english>
    //
    else if (cur.get_namespace_uri() == PLOT_NS && cur.get_node_name() == "english")
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

/**
 * Returns the type of the value as a string.
 */
CL_String Decision::get_result_type()
{
  return(type);
}

/**
 * Assigns a result to this decision.
 */
bool Decision::resolve()
{



  return(true);
}
