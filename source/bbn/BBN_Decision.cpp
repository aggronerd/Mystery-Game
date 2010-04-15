#include <string>
#include <vector>
#include <exception>
#include <list>

#include "BBN_Decision.h"
#include "BBN_Plot.h"
#include "BBN_Option.h"
#include "BBN_Given.h"
#include "BBN_Prob.h"
#include "../misc/logging.h"
#include "../Application.h"

BBN_Decision::BBN_Decision(BBN_Plot* plot)
{
  DEBUG_MSG("BBN_Decision::BBN_Decision(BBN_Plot*) - Called.")

  _plot = plot;
	_result = 0x0;

	//Set the decision's ID
	_id = get_next_id();
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

long BBN_Decision::get_next_id()
{
  static long current_id;
  if (current_id != NAN)
  {
    current_id = 0;
  }
  else
  {
    current_id += 1;
  }
  return(current_id);
}

void BBN_Decision::load_from_xml(const CL_DomElement& element)
{
  DEBUG_MSG("BBN_Decision::load_from_xml(CL_DomElement) - Called.")

  //Retrieve attributes
  _name = element.get_attribute("name");

  //Parse children:
  DEBUG_MSG(CL_String("BBN_Decision::load_from_xml(CL_DomElement) - Decision name = '") + _name + "'.")

  //Counters for validation
  int options_element_count = 0;
  int option_element_count = 0;
  int probs_element_count = 0;
  int prob_element_count = 0;
  int givens_element_count = 0;
  int given_element_count = 0;

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
      options_element_count ++;
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
          option_element_count++;
        }
       cur2 = cur2.get_next_sibling();
     }
    }
    else if (cur.get_node_name() == "english")
    {
      /*
       * <english></english>
       */
      _english =  static_cast<CL_String>(cur.get_node_value());
    }
    else if (cur.get_node_name() == "givens")
    {
      /*
       * <givens></givens>
       */
      givens_element_count ++;
      CL_DomNode cur2 = cur.get_first_child();
      //Look for 'given' elements.
      while (!cur2.is_null())
      {
        if (cur2.get_node_name() == "given")
        {
          /*
           * <given></given>
           */
          BBN_Given* given = new BBN_Given(this);
          CL_DomElement element = cur2.to_element();
          given->load_from_xml(element);
          add_given(given);
        }
        cur2 = cur2.get_next_sibling();
      }
    }
    else if (cur.get_node_name() == "probs")
    {
      /*
       * <probs></probs>
       */
      probs_element_count ++;
      CL_DomNode cur2 = cur.get_first_child();
      //Look for 'prob' elements.
      while (!cur2.is_null())
      {
        if (cur2.get_node_name() == "prob")
        {
          /*
           * <prob></prob>
           */
          BBN_Prob* prob = new BBN_Prob(this);
          CL_DomElement element = cur2.to_element();
          prob->load_from_xml(element);
          add_prob(prob);
        }
        cur2 = cur2.get_next_sibling();
      }
    }
    else if  (cur.get_node_name() == "dependencies")
    {
       /*
        * <dependencies></dependencies>
        */
      probs_element_count ++;
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

   /*
    * Validation afterwards to report errors.
    */
   if(options_element_count != 1)
   {
     throw CL_Exception("Invalid number of 'options' elements in plot XML.");
   }
   if(option_element_count == 0)
   {
     throw CL_Exception("No 'option' elements found in plot XML.");
   }
}

BBN_Plot* BBN_Decision::get_plot()
{
	throw "Not yet implemented";
}

CL_String BBN_Decision::get_name()
{
	throw "Not yet implemented";
}

void BBN_Decision::set_name(CL_String new_name)
{
	throw "Not yet implemented";
}

int BBN_Decision::get_type()
{
	throw "Not yet implemented";
}

void BBN_Decision::set_type(int new_type)
{
	throw "Not yet implemented";
}

CL_String BBN_Decision::get_english()
{
	throw "Not yet implemented";
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
	throw "Not yet implemented";
}

long BBN_Decision::get_id()
{
	return(_id);
}

void BBN_Decision::load_bn_probabilities(dlib::directed_graph<dlib::bayes_node>::kernel_1a_c* bn)
{
	throw "Not yet implemented";
}

BBN_Option* BBN_Decision::get_result()
{
	throw "Not yet implemented";
}

void BBN_Decision::add_option(BBN_Option* option)
{
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
