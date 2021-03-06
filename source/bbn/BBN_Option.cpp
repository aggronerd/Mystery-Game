#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "BBN_Option.h"
#include "BBN_Decision.h"
#include "BBN_Given.h"
#include "BBN_Prob.h"
#include "../misc/logging.h"
#include "../Application.h"

BBN_Option::BBN_Option(BBN_Decision* decision) : _decision(decision)
{
  DEBUG_MSG("BBN_Option::BBN_Option(BBN_Decision*) - Called.")
}

BBN_Option::~BBN_Option()
{
  DEBUG_MSG("BBN_Option::~BBN_Option() - Called.")
  _decision = 0x0;
}

void BBN_Option::load_from_xml(const CL_DomElement& element)
{
  DEBUG_MSG("BBN_Option::load_from_xml(CL_DomElement) - Called.")

	_name = element.get_attribute("name");
  _english = element.get_attribute("english");

  DEBUG_MSG("BBN_Option::load_from_xml(CL_DomElement) - Option name = '" + _name + "'.")
}

CL_String8 BBN_Option::get_name()
{
	return(_name);
}

void BBN_Option::set_name(const CL_String8& new_name)
{
	_name = new_name;
}

CL_String8 BBN_Option::get_english()
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

void BBN_Option::set_english(const CL_String8& new_english)
{
	_english = new_english;
}

unsigned int BBN_Option::get_id()
{
  return(_id);
}

void BBN_Option::set_id(unsigned int id)
{
  _id = id;
}

BBN_Decision* BBN_Option::get_decision()
{
  return(_decision);
}
