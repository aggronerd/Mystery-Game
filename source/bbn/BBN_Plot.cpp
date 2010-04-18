
#include "../misc/logging.h"
#include "BBN_Plot.h"
#include "BBN_Decision.h"
#include "BBN_Exception.h"

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

  //TODO: Compare with XML schema definition.

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

void BBN_Plot::set_name(CL_String new_name)
{
	_name = new_name;
}

CL_String BBN_Plot::get_name()
{
  return(_name);
}

/**
 * Adds the pointer to an instance of BBN_Decision to _decisions.
 */
void BBN_Plot::add_decision(BBN_Decision* decision)
{
  DEBUG_MSG("BBN_Plot::add_decision(BBN_Decision*) - Called.")
	_decisions.push_back(decision);
}

/**
 * Prepares dlib's bayes net by defining nodes and probabilities.
 */
void BBN_Plot::prepare_bn()
{

  //Destroy existing bayes net.
  if(_bn != 0x0)
  {
    delete(_bn);
  }

  //Create the bayes net.
	_bn = new dlib::directed_graph<dlib::bayes_node>::kernel_1a_c();

	get_bn()->set_number_of_nodes(decisions_count());

  std::vector<BBN_Decision*>::iterator it_de;

  for(it_de = _decisions.begin(); it_de != _decisions.end(); ++it_de)
      (*it_de) -> prepare_bn_node(get_bn());

  for(it_de = _decisions.begin(); it_de != _decisions.end(); ++it_de)
      (*it_de) -> load_bn_probabilities(get_bn());

  update_bn_solution();

}

long BBN_Plot::decisions_count()
{
	return(_decisions.size());
}

/**
 * Returns a pointer to the decision object with the
 * name specified in the parameter. If it cannot be
 * found the function returns a null pointer (0x0).
 *
 * Currently only iterates through all decisions.
 * Therefore is slow for instances when there are
 * many decisions. However allows names to be
 * changed. TODO: What is the value of this given
 * that linkages between objects are still defined
 * by string paths given in the XML file and not by
 * pointers?
 */
BBN_Decision* BBN_Plot::get_decision(const CL_String& name)
{
  std::vector<BBN_Decision*>::iterator it_decision;
  for(it_decision = _decisions.begin(); it_decision != _decisions.end(); ++it_decision)
    if((*it_decision)->get_name() == name)
      return(*it_decision);
  return(0x0);
}

dlib::directed_graph<dlib::bayes_node>::kernel_1a_c* BBN_Plot::get_bn()
{
	return(_bn);
}

/**
 * Updates the Bayes Net solution to reflect changes in bn.
 */
void BBN_Plot::update_bn_solution()
{
  if(_bn != 0x0)
  {
    if(_bn_join_tree != 0x0)
      delete _bn_join_tree;

    _bn_join_tree = new join_tree_type();

    // Now we need to populate the join_tree with data from our bayesian network.  The next
    // function calls do this.  Explaining exactly what they do is outside the scope of this
    // example.  Just think of them as filling join_tree with information that is useful
    // later on for dealing with our bayesian network.
    dlib::create_moral_graph(*(_bn), *(_bn_join_tree));
    create_join_tree( *(_bn_join_tree),  *(_bn_join_tree));

    // Now that we have a proper join_tree we can use it to obtain a solution to our
    // bayesian network.  Doing this is as simple as declaring an instance of
    // the bayesian_network_join_tree object as follows:
    if(_bn_current_solution != 0x0)
      delete _bn_current_solution;

    _bn_current_solution = new dlib::bayesian_network_join_tree(*(_bn), *(_bn_join_tree));

  }
  else
  {
    throw(BBN_Exception("BBN_Plot::update_bn_solution() called when _bn is not defined."));
  }
}

BBN_Option* BBN_Plot::query_result(CL_String option_name)
{
	throw "Not yet implemented";
}

dlib::bayesian_network_join_tree* BBN_Plot::get_bn_current_solution()
{
	throw "Not yet implemented";
}

std::vector<BBN_Decision*>* BBN_Plot::get_decisions()
{
  return(&_decisions);
}

/**
 * Returns a pointer to an option defined by path. If it
 * cannot be found then the function returns null (0x0).
 */
BBN_Option* BBN_Plot::get_option(const CL_String& path)
{
  int n = path.find_first_of('.',0);

  CL_String decision_name = path.substr(0,n);
  CL_String option_name = path.substr(n+1,path.size()-n-1);

  BBN_Decision* decision = get_decision(decision_name);
  if(decision == 0x0)
  {
    DEBUG_MSG("BBN_Option* BBN_Plot::get_option(const CL_String&) - Attempt to get decision '" + decision_name + "' failed." )
    return(0x0);
  }
  else
  {
    BBN_Option* option = decision->get_option(option_name);
    if(option == 0x0)
    {
      DEBUG_MSG("BBN_Option* BBN_Plot::get_option(const CL_String&) - Attempt to get option '" + option_name + "' failed." )
      return(0x0);
    }
    else
    {
      return(option);
    }
  }

}
