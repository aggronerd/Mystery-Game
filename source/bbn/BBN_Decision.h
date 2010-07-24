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
class BBN_Prob;
class BBN_Option;
class BBN_Given;

class BBN_Decision
{
private:

  unsigned long _id;
  CL_String8 _name;
  CL_String8 _english;
  int _type;

	BBN_Plot* _plot;
	BBN_Option* _result;
	std::list<CL_String8> _dependencies;
	std::vector<BBN_Option*> _options;
	std::vector<BBN_Given*> _givens;
	std::vector<BBN_Prob*> _probs;

	int _next_option_id;

public:

	BBN_Decision(BBN_Plot* plot);
	virtual ~BBN_Decision();
	void load_from_xml(const CL_DomElement& element);
	BBN_Plot* get_plot(void);
	CL_String8 get_name(void);
	void set_name(CL_String8 new_name);
	int get_type(void);
	void set_type(int new_type);
	CL_String8 get_english(void);
	void set_english(CL_String8 new_english);
	void prepare_bn_node(dlib::directed_graph<dlib::bayes_node>::kernel_1a_c* bn);
	unsigned long get_id(void);
	void load_bn_probabilities(dlib::directed_graph<dlib::bayes_node>::kernel_1a_c* bn);
	BBN_Option* get_result(void);
	bool has_generated_result(void);
	BBN_Option* get_option(const CL_String8&);
	std::vector<BBN_Option*>* get_options(void);
	bool set_result(const CL_String8&);

	void add_option(BBN_Option*);
	void add_dependency(CL_String8 decision_path);
	void add_given(BBN_Given*);
	void add_prob(BBN_Prob*);
};

#endif
