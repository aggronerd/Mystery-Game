/*
 * Plot.cpp
 *
 *  Created on: 15 Jan 2010
 *      Author: greg
 */

#include "Plot.h"
#include "Decision.h"
#include "../logging.h"
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

  DEBUG_MSG("Plot::Plot(const char*) - Found plot '" + root.get_attribute("name") + "'")

  //Iterate through decisions.
  DEBUG_MSG("Plot::Plot(const char*) - Constructing decisions.");
  CL_DomNode cur = root.get_first_child();
  while (!cur.is_null())
  {
    if (cur.get_namespace_uri() == ns_plot && cur.get_node_name() == "decision")
    {
      //Delegate parsing of decision elements to the Decision class:
      CL_DomElement element = cur.to_element();
      decisions.push_back(Decision(element));
    }
    cur = cur.get_next_sibling();
  }
}

Plot::~Plot()
{
  DEBUG_MSG("Plot::~Plot() - Called.")

}

void Plot::parseXML()
{

}
