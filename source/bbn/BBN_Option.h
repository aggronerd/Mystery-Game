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
  /**
   * This is unique and sequential within the
   * object's parent decision. It is required
   * by dlib's bayes net stuff.
   */
  unsigned int _id;

public:
  BBN_Option(BBN_Decision* decision);
  virtual ~BBN_Option();
  CL_String get_name();
  CL_String get_english();
  void load_from_xml(const CL_DomElement&);
  void set_name(const CL_String&);
  void set_english(const CL_String&);
  BBN_Decision* get_decision(void);
  unsigned int get_id(void);
  void set_id(unsigned int);
};

#endif
