/*
 * Plot.cpp
 *
 *  Created on: 15 Jan 2010
 *      Author: greg
 */

#include "Plot.h"
#include "../logging.h"
#include "Decision.h"
#include <ClanLib/core.h>

/**
 * Constructs a tree from the specified XML file.
 */
Plot::Plot(const char* filename)
{
  DEBUG_MSG("Plot::Plot(const char*) - Called.")

  //Create a file object.
  CL_String cl_filename = filename;
  CL_File xmlFile(cl_filename); //TODO: Catch if cannot open

  CL_String ns_plot = "http://www.gregorydoran.co.uk/plot";

  DEBUG_MSG("Plot::Plot(const char*) - Creating CL_DomDocument.")
  CL_DomDocument document(xmlFile);

  DEBUG_MSG("Plot::Plot(const char*) - Getting plot element.")
  CL_DomElement root = document.get_document_element();

  //Retrieve attributes
  name = root.get_attribute("name");

  //Parse children:
  DEBUG_MSG(CL_String("Plot::Plot(const char*) - Processing children for '") + name + "'.")
  CL_DomNode cur = root.get_first_child();
  while (!cur.is_null())
  {
    if (cur.get_namespace_uri() == ns_plot && cur.get_node_name() == "decision")
    {
      //Delegate parsing of decision elements to the Decision class:
      CL_DomElement element = cur.to_element();
      decisions.push_back(new Decision(element));
    }
    cur = cur.get_next_sibling();
  }
}

Plot::~Plot()
{
  DEBUG_MSG("Plot::~Plot() - Called.")

  //Deleting decision objects.
  std::list<Decision *>::iterator it_des;
  for(it_des = decisions.begin(); it_des != decisions.end(); ++it_des)
    delete (*it_des);
  decisions.clear();
}
