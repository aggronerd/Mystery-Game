#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "BBN_Option.h"
#include "BBN_Decision.h"
#include "BBN_Given.h"
#include "BBN_Prob.h"
#include "../misc/logging.h"

BBN_Option::BBN_Option(BBN_Decision* decision)
{
  DEBUG_MSG("BBN_Option::BBN_Option(BBN_Decision*) - Called.")
}

BBN_Option::~BBN_Option()
{
  DEBUG_MSG("BBN_Option::~BBN_Option() - Called.")
  _decision = 0x0;
}

void BBN_Option::load_from_xml(CL_DomElement element)
{
  DEBUG_MSG("BBN_Option::load_from_xml(CL_DomElement) - Called.")

	_name = static_cast<CL_String>(element.get_attribute("name"));
  DEBUG_MSG("BBN_Option::load_from_xml(CL_DomElement) - Option name = '" + _name + "'.")


  CL_DomNode cur = element.get_first_child();
  while (!cur.is_null())
  {
    if (cur.get_node_name() == "english")
    {
      /*
       * <english></english>
       */
      _english = static_cast<CL_String>(cur.get_node_value());
      DEBUG_MSG("BBN_Option::load_from_xml(CL_DomElement) - Option english = '" + _english + "'.")
    }
    cur = cur.get_next_sibling();
  }

}

CL_String BBN_Option::get_name()
{
	throw "Not yet implemented";
}

void BBN_Option::set_name(CL_String new_name)
{
	throw "Not yet implemented";
}

CL_String BBN_Option::get_english()
{
	throw "Not yet implemented";
}

void BBN_Option::set_english(CL_String new_english)
{
	throw "Not yet implemented";
}

