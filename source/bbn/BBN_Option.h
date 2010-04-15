#ifndef __BBN_Option_h__
#define __BBN_Option_h__

#include <vector>
#include <exception>
#include <ClanLib/core.h>
#include "BBN_Given.h"
#include "BBN_Prob.h"

class BBN_Decision;

class BBN_Option
{
private:
  CL_String _name;
  CL_String _english;
  BBN_Decision* _decision;

public:
  BBN_Option(BBN_Decision* decision);
  virtual ~BBN_Option();
  CL_String get_name();
  CL_String get_english();
  void load_from_xml(CL_DomElement element);
  void set_name(CL_String new_name);
  void set_english(CL_String new_english);
};

#endif
