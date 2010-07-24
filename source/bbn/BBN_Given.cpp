#include <vector>
#include <exception>
#include "BBN_Given.h"
#include "BBN_Prob.h"
#include "BBN_Exception.h"
#include "BBN_Decision.h"
#include "BBN_Plot.h"
#include "BBN_Option.h"
#include "../misc/logging.h"

BBN_Given::BBN_Given(BBN_Decision* decision)
{
  DEBUG_MSG("BBN_Given::BBN_Given(BBN_Decision*) - Called.")
  _decision = decision;
}

BBN_Given::~BBN_Given()
{
  DEBUG_MSG("BBN_Given::~BBN_Given() - Called.")

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

  _decision = 0x0;
}

void BBN_Given::load_from_xml(CL_DomElement element)
{
  DEBUG_MSG("BBN_Given::load_from_xml(CL_DomElement) - Called.")

  //Retrieve attributes
  _option = element.get_attribute("option");
  DEBUG_MSG("BBN_Given::load_from_xml(CL_DomElement) - Given option = '"+_option+"'.")

  //Fetch the first child element
  CL_DomNode cur = element.get_first_child();
  CL_DomNode curChild;

  /*
   * Loop through first elements.
   */
  while (!cur.is_null())
  {
    if (cur.get_node_name() == CL_String8("givens"))
    {
      /*
       * <givens></givens>
       */
      curChild = cur.get_first_child();
      while(!curChild.is_null())
      {
        if(curChild.get_node_name() == CL_String8("given"))
        {
          /*
           * <given></given>
           */
          BBN_Given* given = new BBN_Given(_decision);
          CL_DomElement element = curChild.to_element();
          given->load_from_xml(element);
          add_given(given);
        }
        curChild = curChild.get_next_sibling();
      }
    }
    if (cur.get_node_name() == CL_String8("probs"))
    {
      /**
        * <probs></probs>
        */
      curChild = cur.get_first_child();
      while(!curChild.is_null())
      {
        if(curChild.get_node_name() == CL_String8("prob"))
        {
          /*
           * <prob></prob>
           */
          BBN_Prob* prob = new BBN_Prob(_decision);
          CL_DomElement element = curChild.to_element();
          prob->load_from_xml(element);
          add_prob(prob);
        }
        curChild = curChild.get_next_sibling();
      }
    }
    cur = cur.get_next_sibling();
  }

  //TODO:Validate
}

void BBN_Given::set_bn_probabilities(dlib::directed_graph<dlib::bayes_node>::kernel_1a_c* bn, dlib::assignment parent_states)
{
  //Apply parent states to probability definition for the bayes net.
  BBN_Option* option = get_decision()->get_plot()->get_option(_option);

  if(option == 0x0)
  {
    throw(BBN_Exception("Error finding option '" + _option + "' in given for decision " + get_decision()->get_name()));
  }
  else
  {
    //Applies given rule to any subsequent recursive calls.
    parent_states.add(option->get_decision()->get_id(),option->get_id());

    if(_givens.size() > 0)
    {
      std::vector<BBN_Given*>::iterator it_given;
      for(it_given = _givens.begin(); it_given != _givens.end(); ++it_given)
      {
        (*(it_given))->set_bn_probabilities(get_decision()->get_plot()->get_bn(),parent_states);
      }
    }
    else if(_probs.size() > 0)
    {
      std::vector<BBN_Prob*>::iterator it_prob;
      for(it_prob = _probs.begin(); it_prob != _probs.end(); ++it_prob)
      {
        (*(it_prob))->set_bn_probability(get_decision()->get_plot()->get_bn(),parent_states);
      }
    }
    else
    {
      throw(BBN_Exception("No given/prob objects found to extract probabilities from in given for decision '" + get_decision()->get_name() + "' where option = '" + _option + "'."));
    }

  }
}

BBN_Decision* BBN_Given::get_decision()
{
  return(_decision);
}

void BBN_Given::add_given(BBN_Given* given)
{
  _givens.push_back(given);
}

void BBN_Given::add_prob(BBN_Prob* prob)
{
  _probs.push_back(prob);
}

