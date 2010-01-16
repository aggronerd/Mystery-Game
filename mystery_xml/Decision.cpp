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

  CL_String ns_plot = "http://www.gregorydoran.co.uk/plot";

  //Retrieve attributes.
  name = element.get_attribute_ns(ns_plot, "name");

  //TODO: Process <english> tag.

  Application::log(LOG_LEVEL_DEBUG, CL_String("Decision::Decision(const CL_DomElement&) - Processing options for '") + name + CL_String("'."));

  //TODO: Process options.

}

Decision::~Decision()
{
  // TODO Auto-generated destructor stub
}
