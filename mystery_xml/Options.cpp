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

  DEBUG_MSG("Options::Options(const CL_DomElement&) - Called.");

  //Parse options

}

Options::~Options()
{

  Application::log(LOG_LEVEL_DEBUG, "Options::~Options() - Called.");

  // Delete all options
  options.clear(); //TODO: Ensure clears the memory.
}
