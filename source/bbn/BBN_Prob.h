#ifndef __BBN_Prob_h__
#define __BBN_Prob_h__

#include <exception>
#include <ClanLib/core.h>
#include "../dlib/bayes_utils.h"
#include "../dlib/graph_utils.h"
#include "../dlib/graph.h"
#include "../dlib/directed_graph.h"

class BBN_Decision;

class BBN_Prob
{

private:
  float _probability;
  /**
   * option is the path to the option.
   */
  CL_String _option;
  BBN_Decision* _decision;

public:
  BBN_Prob(BBN_Decision*);
  virtual ~BBN_Prob();
  void load_from_xml(CL_DomElement element);
  void set_bn_probability(dlib::directed_graph<dlib::bayes_node>::kernel_1a_c* bn, dlib::assignment parent_state);
  BBN_Decision* get_decision(void);

};

#endif
