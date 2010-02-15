/*
 * Plot.cpp
 *
 *  Created on: 15 Jan 2010
 *      Author: greg
 */

#include "Plot.h"
#include "../misc/logging.h"
#include "Option.h"

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
    if (cur.get_namespace_uri() == PLOT_NS && cur.get_node_name() == "decisions")
    {
      //Delegate parsing of decisions element to the Decisions class:
      CL_DomElement element = cur.to_element();
      decisions = new Decisions(this, element);
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

/**
 * Adds the Option object to the map
 * accessible by index.
 */
void Plot::addOption(Option* option)
{
  DEBUG_MSG("Plot::addOption(Option*) - Called.")
  //TODO: Check ID isn't already in use.
  options[option->getId()] = option;
}
