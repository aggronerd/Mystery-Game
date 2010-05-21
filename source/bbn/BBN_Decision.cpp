#include <string>
#include <vector>
#include <exception>
#include <list>

#include "BBN_Decision.h"
#include "BBN_Option.h"
#include "BBN_Given.h"
#include "BBN_Prob.h"
#include "BBN_Plot.h"
#include "BBN_Random.h"
#include "../misc/logging.h"
#include "../Application.h"
#include "BBN_Exception.h"

BBN_Decision::BBN_Decision(BBN_Plot* plot)
{
  DEBUG_MSG("BBN_Decision::BBN_Decision(BBN_Plot*) - Called.")

  _plot = plot;
  _result = 0x0;
  _next_option_id = 0;

  //Set the decision's ID
  _id = plot->get_next_decision_id();
}

BBN_Decision::~BBN_Decision()
{
  DEBUG_MSG("BBN_Decision::~BBN_Decision() - Called.")

  // Delete all options
  std::vector<BBN_Option*>::iterator it_op;
  for(it_op = _options.begin(); it_op != _options.end(); ++it_op)
      delete (*it_op);
  _options.clear();

  // Delete all givens
  std::vector<BBN_Given*>::iterator it_gi;
  for(it_gi = _givens.begin(); it_gi != _givens.end(); ++it_gi)
      delete (*it_gi);
  _givens.clear();

  // Delete all givens
  std::vector<BBN_Prob*>::iterator it_pr;
  for(it_pr = _probs.begin(); it_pr != _probs.end(); ++it_pr)
      delete (*it_pr);
  _probs.clear();

  _plot = 0x0;
  _result = 0x0;
}

void BBN_Decision::load_from_xml(const CL_DomElement& element)
{
  DEBUG_MSG("BBN_Decision::load_from_xml(CL_DomElement) - Called.")

  //Retrieve attributes
  _name = element.get_attribute("name");
  _english = element.get_attribute("english");

  //Parse children:
  DEBUG_MSG(CL_String("BBN_Decision::load_from_xml(CL_DomElement) - Decision name = '") + _name + "'.")

  //Fetch the first child element
  CL_DomNode cur = element.get_first_child();

  /*
   * Loop through first elements.
   */
  while (!cur.is_null())
  {

    if (cur.get_node_name() == "options")
    {
      /*
       * <options></options>
       */
      CL_DomNode cur2 = cur.get_first_child();
      //Look for 'option' elements.
      while (!cur2.is_null())
      {
        if (cur2.get_node_name() == "option")
        {
          BBN_Option* option = new BBN_Option(this);
          CL_DomElement element = cur2.to_element();
          option->load_from_xml(element);
          add_option(option);
        }
       cur2 = cur2.get_next_sibling();
     }
    }
    else if (cur.get_node_name() == "probabilities")
    {
      /*
       * <probabilities></probabilities>
       */
      CL_DomNode cur2 = cur.get_first_child();

      while(!cur2.is_null())
      {
        if (cur2.get_node_name() == "givens")
        {
          /*
           * <givens></givens>
           */
          CL_DomNode cur3 = cur2.get_first_child();

          //Look for 'given' elements.
          while (!cur3.is_null())
          {
            if (cur3.get_node_name() == "given")
            {
              /*
               * <given></given>
               */
              BBN_Given* given = new BBN_Given(this);
              CL_DomElement element = cur3.to_element();
              given->load_from_xml(element);
              add_given(given);
            }
            cur3 = cur3.get_next_sibling();
          }
        }
        else if (cur2.get_node_name() == "probs")
        {
          /*
           * <probs></probs>
           */
          CL_DomNode cur3 = cur2.get_first_child();

          //Look for 'prob' elements.
          while (!cur3.is_null())
          {
            if (cur3.get_node_name() == "prob")
            {
              /*
               * <prob></prob>
               */
              BBN_Prob* prob = new BBN_Prob(this);
              CL_DomElement element = cur3.to_element();
              prob->load_from_xml(element);
              add_prob(prob);
            }
            cur3 = cur3.get_next_sibling();
          }
        }

        cur2 = cur2.get_next_sibling();

      }
    }
    else if  (cur.get_node_name() == "dependencies")
    {
       /*
        * <dependencies></dependencies>
        */
      CL_DomNode cur2 = cur.get_first_child();
      //Look for 'dependency' elements.
      while (!cur2.is_null())
      {
        if (cur2.get_node_name() == "dependency")
        {
          CL_DomElement element = cur2.to_element();
          CL_String decision_path = static_cast<CL_String>(element.get_attribute("decision"));
          add_dependency(decision_path);
        }
        cur2 = cur2.get_next_sibling();
      }
    }
    else
    {
      Application::log(LOG_LEVEL_WARN,CL_String("BBN_Decision::load_from_xml(CL_DomElement) - Warning: unrecognised element '") + static_cast<CL_String>(cur.get_node_name()) + CL_String("' in decision."));
    }

     cur = cur.get_next_sibling();

   }
}

BBN_Plot* BBN_Decision::get_plot()
{
	return(_plot);
}

CL_String BBN_Decision::get_name()
{
	return(_name);
}

void BBN_Decision::set_name(CL_String new_name)
{
	_name = new_name;
}

int BBN_Decision::get_type()
{
	return(_type);
}

void BBN_Decision::set_type(int new_type)
{
	_type = new_type;
}

CL_String BBN_Decision::get_english()
{
  if(!_english.empty())
  {
    return(_english);
  }
  else
  {
    return(get_name());
  }
}

void BBN_Decision::set_english(CL_String new_english)
{
  _english = new_english;
}

void BBN_Decision::add_dependency(CL_String decision_path)
{
	_dependencies.push_back(decision_path);
}

void BBN_Decision::prepare_bn_node(dlib::directed_graph<dlib::bayes_node>::kernel_1a_c* bn)
{

  DEBUG_MSG("void BBN_Decision::prepare_bn_node(dlib::directed_graph<dlib::bayes_node>::kernel_1a_c*) - Called for '" + _name + "'.")

  /*
   * Adds edges to bayes net.
   */
  std::list<CL_String>::iterator it_de;
  for(it_de = _dependencies.begin(); it_de != _dependencies.end(); ++it_de)
  {
    BBN_Decision* predecessor = get_plot()->get_decision((*it_de));
    long predecessor_id = predecessor->get_id();

    //Add edge to the bayes net.
    DEBUG_MSG("void BBN_Decision::prepare_bn_node(dlib::directed_graph<dlib::bayes_node>::kernel_1a_c*) - Adding edge '" + predecessor->get_name() +
        "' (" + CL_StringHelp::uint_to_text(static_cast<unsigned int>(predecessor_id)) + ") -> '" + this->get_name() + "' (" +
        CL_StringHelp::uint_to_text(static_cast<unsigned int>(get_id())) + ").")
    get_plot()->get_bn()->add_edge(predecessor_id,get_id());
  }

  /*
   * Sets the number of values for the node.
   */
  dlib::bayes_node_utils::set_node_num_values(*(get_plot()->get_bn()),get_id(),_options.size());

}

unsigned long BBN_Decision::get_id()
{
	return(_id);
}

/**
 * Takes probabilities found in given and prob objects and loads them into the bayes net.
 */
void BBN_Decision::load_bn_probabilities(dlib::directed_graph<dlib::bayes_node>::kernel_1a_c* bn)
{
  //Initial parent state for givens in BBN
  dlib::assignment parent_states; //Given nothing for now.

  if(_givens.size() > 0)
  {
    std::vector<BBN_Given*>::iterator it_given;
    for(it_given = _givens.begin(); it_given != _givens.end(); ++it_given)
    {
      (*(it_given))->set_bn_probabilities(get_plot()->get_bn(),parent_states);
    }
  }
  else if(_probs.size() > 0)
  {
    std::vector<BBN_Prob*>::iterator it_prob;
    for(it_prob = _probs.begin(); it_prob != _probs.end(); ++it_prob)
    {
      (*(it_prob))->set_bn_probability(get_plot()->get_bn(),parent_states);
    }
  }
  else
  {
    throw(BBN_Exception("No given/prob objects found to extract probabilities from in decision '" + _name + "'."));
  }
}

/**
 * If is not defined compares random number with probabilities to pick an outcome.
 */
BBN_Option* BBN_Decision::get_result()
{
  DEBUG_MSG("BBN_Option* BBN_Decision::get_result() - Called for '" + get_name() + "'.")

	if(_result == 0x0)
	{
	  float rand = BBN_Random::get_next_float();
	  float cum_prob = 0;
	  int n = -1;

	  DEBUG_MSG("BBN_Option* BBN_Decision::get_result() - rand = " + CL_StringHelp::float_to_text(rand) + ".")

	  do
	  {
	    n++;
	    cum_prob += get_plot()->get_bn_current_solution()->probability(get_id())(_options.at(n)->get_id());
	    DEBUG_MSG("BBN_Option* BBN_Decision::get_result() - cum_prob = " + CL_StringHelp::float_to_text(cum_prob) + ".")
	  }
	  while(rand > cum_prob);

	  //Set result
	  _result = _options.at(n);

	  //Update bn solution
	  dlib::bayes_node_utils::set_node_value(*(get_plot()->get_bn()),get_id(), _result->get_id());
	  dlib::bayes_node_utils::set_node_as_evidence(*(get_plot()->get_bn()), get_id());
	  get_plot()->update_bn_solution();

	}
	return(_result);
}

void BBN_Decision::add_option(BBN_Option* option)
{
  //Set the ID which is unique between all options for this decision
  option->set_id(_next_option_id);
  _next_option_id ++;

  _options.push_back(option);
}

void BBN_Decision::add_given(BBN_Given* given)
{
  _givens.push_back(given);
}

void BBN_Decision::add_prob(BBN_Prob* prob)
{
  _probs.push_back(prob);
}

/**
 * Returns a pointer to the option with the name given
 * in the parameter. Returns null (0x0) if is not found
 *
 * No fancy method is employed in searching it simply
 * iterates through the vector but allows changing of names.
 */
BBN_Option* BBN_Decision::get_option(const CL_String& name)
{
  std::vector<BBN_Option*>::iterator it_option;
  for(it_option = _options.begin(); it_option != _options.end(); ++it_option)
    if((*it_option)->get_name() == name)
      return(*it_option);
  return(0x0);
}

/**
 * Sets the result of this decision to the option defined in option_name.
 * Returns true if successful and false if not.
 */
bool BBN_Decision::set_result(const CL_String& option_name)
{
  bool result = false;
  std::vector<BBN_Option*>::iterator it_option;

  for(it_option = _options.begin(); it_option != _options.end(); ++it_option)
  {
    if((*it_option)->get_name() == option_name)
    {
      //Set result
      _result = (*it_option);

      //Update bn solution
      dlib::bayes_node_utils::set_node_value(*(get_plot()->get_bn()),get_id(), _result->get_id());
      dlib::bayes_node_utils::set_node_as_evidence(*(get_plot()->get_bn()), get_id());
      get_plot()->update_bn_solution();

      result = true;
    }
  }

  return(result);

}
