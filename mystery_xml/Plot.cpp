/*
 * Plot.cpp
 *
 *  Created on: 15 Jan 2010
 *      Author: greg
 */

#include "Plot.h"
#include "../App.h"
#include <ClanLib/core.h>

Plot::Plot(const char* filename)
{
  Application::log(LOG_LEVEL_DEBUG, "Plot constructor called.");

  //Create a file object.
  CL_String cl_filename = filename;
  xmlFile = new CL_File(cl_filename); //TODO: Catch if cannot open

  parseXML();
}

Plot::~Plot()
{
  Application::log(LOG_LEVEL_DEBUG, "Plot destructor called.");

  xmlFile->close();

}

void Plot::parseXML()
{
  CL_String ns_plot = "http://www.gregorydoran.co.uk/plot";
  CL_String plotname;

  Application::log(LOG_LEVEL_DEBUG, "Plot::parseXML() - Creating CL_DomDocument.");
  CL_DomDocument document(*(xmlFile));

  Application::log(LOG_LEVEL_DEBUG, "Plot::parseXML() - Getting root element.");
  CL_DomElement root = document.get_document_element();

  Application::log(LOG_LEVEL_DEBUG, root.get_attribute("name"));

  Application::log(LOG_LEVEL_DEBUG, "Plot::parseXML() - Getting plot element.");
  CL_DomElement body = root.named_item_ns(ns_plot, "plot").to_element();

  Application::log(LOG_LEVEL_DEBUG, body.get_attribute("name"));

  /*CL_DomNode cur = body.get_first_child();
  while (cur.is_node())
  {
          if (cur.get_namespace_uri() == ns_plot && cur.get_node_name() == "desision")
          {
                  CL_DomElement element = cur.to_element();
                  CL_String name = element.get_attribute_ns(ns_example, "name");
                  CL_String value = element.get_text();
                  CL_Console::write_line("Message %1: %2", name, value);
          }
          cur = cur.get_next_sibling();
  }*/
}
