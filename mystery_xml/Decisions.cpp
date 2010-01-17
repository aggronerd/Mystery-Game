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

}

Decisions::~Decisions()
{
  DEBUG_MSG("Decisions::~Decisions() - Called.")

  //Deleting decision objects.
  std::list<Decision *>::iterator it_des;
  for(it_des = decisions.begin(); it_des != decisions.end(); ++it_des)
    delete (*it_des);
  decisions.clear();
}
