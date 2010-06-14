
#include "../misc/logging.h"
#include "BBN_Plot.h"
#include "BBN_Option.h"
#include "BBN_Decision.h"
#include "BBN_Exception.h"
#include "BBN_Random.h"

/**
 * Copies defined results from another bayes net.
 *
 * @param existing
 */
void BBN_Plot::clone_results(BBN_Plot* existing)
{
	//Duplicate results
	std::vector<BBN_Decision*>::iterator it_source;
	for(it_source = existing->get_decisions()->begin(); it_source != existing->get_decisions()->end(); ++it_source)
	{
		if((*it_source)->has_generated_result())
		{
			//TODO: Change so it doesn't resolve bayesian net with each set command.
			this->set_result((*it_source)->get_name(),(*it_source)->get_result()->get_name());
		}
	}
}

BBN_Plot::BBN_Plot(const CL_String& file_name)
{
  DEBUG_MSG("BBN_Plot::BBN_Plot(const CL_String&) - Called.")

  _bn_current_solution = 0x0;
  _bn_join_tree = 0x0;
  _bn = 0x0;
  _next_decision_id = 0;
  _file_name = file_name;

  CL_File xmlFile(file_name); //TODO: Catch if cannot open

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
    if (cur.get_node_name() == CL_String("decisions"))
    {
      //'decisions' element encountered
      decisions_element_count ++;
      CL_DomNode cur2 = cur.get_first_child();
      /*
       * Look for 'decision elements.
       */
      while (!cur2.is_null())
      {
        if (cur2.get_node_name() == CL_String("decision"))
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

  clear_bn();

  BBN_Random::reset();
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
  clear_bn();

  //Create the bayes net.
  _bn = new dlib::directed_graph<dlib::bayes_node>::kernel_1a_c();

  long number_of_decisions = decisions_count();
  get_bn()->set_number_of_nodes(number_of_decisions);

  std::vector<BBN_Decision*>::iterator it_de;

  for(it_de = _decisions.begin(); it_de != _decisions.end(); ++it_de)
      (*it_de) -> prepare_bn_node(get_bn());

  for(it_de = _decisions.begin(); it_de != _decisions.end(); ++it_de)
      (*it_de) -> load_bn_probabilities(get_bn());

  _bn_join_tree = new join_tree_type();

  // Populate the join_tree with data from the bayesian network.
  dlib::create_moral_graph(*(_bn), *(_bn_join_tree));
  create_join_tree( *(_bn_join_tree),  *(_bn_join_tree));

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
  if(_bn != 0x0 && _bn_join_tree != 0x0)
  {
    // Obtain a solution to the bayesian network.
    if(_bn_current_solution != 0x0)
      delete _bn_current_solution;
    _bn_current_solution = new dlib::bayesian_network_join_tree(*(_bn), *(_bn_join_tree));
  }
  else
  {
    throw(BBN_Exception("BBN_Plot::update_bn_solution() called when _bn or _bn_join_tree is not defined."));
  }
}

/**
 * Destroys all bayes net objects.
 */
void BBN_Plot::clear_bn()
{
  if(_bn_join_tree != 0x0)
  {
	_bn_join_tree->clear();
	delete(_bn_join_tree);
	_bn_join_tree = 0x0;
  }

  if(_bn_current_solution != 0x0)
  {
	delete(_bn_current_solution);
	_bn_current_solution = 0x0;
  }

  if(_bn != 0x0)
  {
	_bn->clear();
	delete(_bn);
	_bn = 0x0;
  }
}

/**
 * Returns the result for the decision. Returns null (0x0) if the decision isn't found.
 */
BBN_Option* BBN_Plot::query_result(CL_String decision_name)
{
	BBN_Decision* decision = get_decision(decision_name);
	if(decision != 0x0)
	{
	  BBN_Option* result = decision->get_result();
	  return(result);
	}
	else
	{
	  return(0x0);
	}
}

dlib::bayesian_network_join_tree* BBN_Plot::get_bn_current_solution()
{
	return(_bn_current_solution);
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

/**
 * Sets the value of a decision. Returns true if successful.
 */
bool BBN_Plot::set_result(const CL_String& decision_path, const CL_String& value)
{
  bool result = false;

  BBN_Decision* decision = get_decision(decision_path);
  if(decision != 0x0)
  {
    result = decision->set_result(value);
  }

  return(result);
}

unsigned long BBN_Plot::get_next_decision_id()
{
  unsigned long id = _next_decision_id;
  _next_decision_id += 1;
  return(id);
}

CL_String BBN_Plot::get_file_name()
{
	return(_file_name);
}
