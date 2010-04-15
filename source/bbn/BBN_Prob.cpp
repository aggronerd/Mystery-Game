#include <vector>
#include <exception>
#include "BBN_Prob.h"
#include "BBN_Decision.h"
#include "../misc/logging.h"

void BBN_Prob::load_from_xml(CL_DomElement element)
{
  DEBUG_MSG("BBN_Prob::load_from_xml(CL_DomElement) - Called.")

	_probability = CL_StringHelp::text_to_float(element.get_attribute("value"));
  DEBUG_MSG("BBN_Prob::load_from_xml(CL_DomElement) - Prob value = '" + CL_StringHelp::float_to_text(_probability) + "'.")

	_option = static_cast<CL_String>(element.get_attribute("option"));
	DEBUG_MSG("BBN_Prob::load_from_xml(CL_DomElement) - Prob option = '" + _option + "'.")
}

BBN_Prob::BBN_Prob(BBN_Decision* decision)
{
  DEBUG_MSG("BBN_Prob::BBN_Prob(BBN_Decision*) - Called.")
  _decision = decision;
}

BBN_Prob::~BBN_Prob()
{
  DEBUG_MSG("BBN_Prob::~BBN_Prob() - Called.")
  _decision = 0x0;
}

void BBN_Prob::set_bn_probability(dlib::directed_graph<dlib::bayes_node>::kernel_1a_c* bn, dlib::assignment parent_state)
{
	throw "Not yet implemented";
}

