/*
 * Plot.cpp
 *
 *  Created on: 15 Jan 2010
 *      Author: greg
 */

#include "Plot.h"
#include "../logging.h"
#include <ClanLib/core.h>

/**
 * Constructs a tree from the specified XML file.
 */
Plot::Plot(const char* filename)
{
  DEBUG_MSG("Plot::Plot(const char*) - Called.")

  //Reset Decisions object pointer to null
  decisions = 0x0;

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
    if (cur.get_namespace_uri() == ns_plot && cur.get_node_name() == "decisions")
    {
      //Delegate parsing of decisions element to the Decisions class:
      CL_DomElement element = cur.to_element();
      decisions = new Decisions(element);
    }
    cur = cur.get_next_sibling();
  }
}

Plot::~Plot()
{
  DEBUG_MSG("Plot::~Plot() - Called.")
  if(decisions != 0x0)
      delete decisions;
}
