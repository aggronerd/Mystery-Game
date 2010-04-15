#ifndef __BBN_Given_h__
#define __BBN_Given_h__

#include <vector>
#include <exception>
#include <ClanLib/core.h>
#include "../dlib/bayes_utils.h"
#include "../dlib/graph_utils.h"
#include "../dlib/graph.h"
#include "../dlib/directed_graph.h"

class BBN_Prob;
class BBN_Decision;

class BBN_Given
{

private:
  /**
   * option is a path to the option.
   */
  CL_String _option;
  std::vector<BBN_Given*> _givens;
  std::vector<BBN_Prob*> _probs;
  BBN_Decision* _decision;

public:
  BBN_Given(BBN_Decision*);
  virtual ~BBN_Given();
  void load_from_xml(CL_DomElement element);
  void set_bn_probabilties(dlib::directed_graph<dlib::bayes_node>::kernel_1a_c* bn, dlib::assignment parent_state);
  void add_given(BBN_Given*);
  void add_prob(BBN_Prob*);

};

#endif
