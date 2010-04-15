
#include "../misc/logging.h"
#include "BBN_Plot.h"
#include "BBN_Decision.h"

BBN_Plot::BBN_Plot(const char* file_name)
{
  DEBUG_MSG("BBN_Plot::BBN_Plot(const char*) - Called.")

  _bn_current_solution = 0x0;
  _bn_join_tree = 0x0;
  _bn = 0x0;

  //Create a file object.
  CL_String cl_filename = file_name;

  CL_File xmlFile(cl_filename); //TODO: Catch if cannot open

  DEBUG_MSG("BBN_Plot::BBN_Plot(const char*) - Creating CL_DomDocument.")
  CL_DomDocument document(xmlFile);

  DEBUG_MSG("BBN_Plot::BBN_Plot(const char*) - Getting plot element.")
  CL_DomElement root = document.get_document_element();

  //Retrieve attributes
  _name = root.get_attribute("name");

  //Parse children:
  DEBUG_MSG(CL_String("BBN_Plot::BBN_Plot(const char*) - Processing children for '") + _name + "'.")

  int decisions_element_count = 0;
  int decision_element_count = 0;

  CL_DomNode cur = root.get_first_child();

  /*
   * Loop through first elements.
   */
  while (!cur.is_null())
  {
    if (cur.get_node_name() == "decisions")
    {
      //'decisions' element encountered
      decisions_element_count ++;
      CL_DomNode cur2 = cur.get_first_child();
      /*
       * Look for 'decision elements.
       */
      while (!cur2.is_null())
      {
        if (cur2.get_node_name() == "decision")
        {
          BBN_Decision* decision = new BBN_Decision(this);
          CL_DomElement element = cur2.to_element();
          decision->load_from_xml(element);
          add_decision(decision);
          decision_element_count++;
        }
        cur2 = cur2.get_next_sibling();
      }
    }
    cur = cur.get_next_sibling();
  }

  /*
   * Validation afterwards to report errors.
   */
  if(decisions_element_count != 1)
  {
    throw CL_Exception("Invalid number of 'decisions' elements in plot XML.");
  }
  if(decision_element_count == 0)
  {
    throw CL_Exception("No 'decision' elements found in plot XML.");
  }
}

BBN_Plot::~BBN_Plot()
{
  DEBUG_MSG("BBN_Plot::~BBN_Plot() - Called.")

  // Delete all decisions
  std::vector<BBN_Decision*>::iterator it_de;
  for(it_de = _decisions.begin(); it_de != _decisions.end(); ++it_de)
      delete (*it_de);
  _decisions.clear();

  if(_bn_join_tree != 0x0)
    delete(_bn_join_tree);

  if(_bn_current_solution != 0x0)
    delete(_bn_current_solution);

  if(_bn != 0x0)
    delete(_bn);
}

void BBN_Plot::set_name(CL_String new_name) {
	throw "Not yet implemented";
}

CL_String BBN_Plot::get_name() {
	throw "Not yet implemented";
}

/**
 * Adds the pointer to an instance of BBN_Decision to _decisions.
 */
void BBN_Plot::add_decision(BBN_Decision* decision)
{
  DEBUG_MSG("BBN_Plot::add_decision(BBN_Decision*) - Called.")
	_decisions.push_back(decision);
}

void BBN_Plot::prepare_bn() {
	throw "Not yet implemented";
}

long BBN_Plot::decisions_count() {
	throw "Not yet implemented";
}

BBN_Decision* BBN_Plot::get_decision(CL_String path) {
	throw "Not yet implemented";
}

dlib::directed_graph<dlib::bayes_node>::kernel_1a_c* BBN_Plot::get_bn() {
	throw "Not yet implemented";
}


/// <summary>
/// Updates the Bayes Net solution to reflect changes in bn.
/// </summary>
void BBN_Plot::update_bn_solution()
{
	throw "Not yet implemented";
}

BBN_Option* BBN_Plot::query_result(CL_String option_name)
{
	throw "Not yet implemented";
}

dlib::bayesian_network_join_tree* BBN_Plot::get_bn_current_solution() {
	throw "Not yet implemented";
}

