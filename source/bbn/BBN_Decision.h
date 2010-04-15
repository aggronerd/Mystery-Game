#ifndef __BBN_Decision_h__
#define __BBN_Decision_h__

#include <vector>
#include <list>
#include <exception>
#include <ClanLib/core.h>
#include "../dlib/bayes_utils.h"
#include "../dlib/graph_utils.h"
#include "../dlib/graph.h"
#include "../dlib/directed_graph.h"

class BBN_Plot;
class BBN_Option;
class BBN_Given;
class BBN_Prob;
class BBN_Plot;

class BBN_Decision
{
private:

  long _id;
  CL_String _name;
  CL_String _english;
  int _type;

	BBN_Plot* _plot;
	BBN_Option* _result;
	std::list<CL_String> _dependencies;
	std::vector<BBN_Option*> _options;
	std::vector<BBN_Given*> _givens;
	std::vector<BBN_Prob*> _probs;

protected:

	static long get_next_id(void);

public:

	BBN_Decision(BBN_Plot* plot);
	virtual ~BBN_Decision();
	void load_from_xml(const CL_DomElement& element);
	BBN_Plot* get_plot(void);
	CL_String get_name(void);
	void set_name(CL_String new_name);
	int get_type(void);
	void set_type(int new_type);
	CL_String get_english(void);
	void set_english(CL_String new_english);
	void prepare_bn_node(dlib::directed_graph<dlib::bayes_node>::kernel_1a_c* bn);
	long get_id(void);
	void load_bn_probabilities(dlib::directed_graph<dlib::bayes_node>::kernel_1a_c* bn);
	BBN_Option* get_result(void);

	void add_option(BBN_Option*);
	void add_dependency(CL_String decision_path);
	void add_given(BBN_Given*);
	void add_prob(BBN_Prob*);
};

#endif
