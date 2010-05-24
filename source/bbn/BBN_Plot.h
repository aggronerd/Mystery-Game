#ifndef __BBN_Plot_h__
#define __BBN_Plot_h__

#include <vector>
#include <exception>
#include <map>
#include <ClanLib/core.h>
#include "../dlib/bayes_utils.h"
#include "../dlib/graph_utils.h"
#include "../dlib/graph.h"
#include "../dlib/directed_graph.h"

class BBN_Decision;
class BBN_Option;

//Type definitions borrowed from the dlib example.
typedef dlib::set<unsigned long>::compare_1b_c set_type;
typedef dlib::graph<set_type, set_type>::kernel_1a_c join_tree_type;

class BBN_Plot
{
private:
  CL_String _name;
	std::map<long, BBN_Decision*> _decisions_by_id;
	std::vector<BBN_Decision*> _decisions;
	unsigned long _next_decision_id;
	CL_String _file_name;

	//dlib stuff:
	join_tree_type* _bn_join_tree;
	dlib::directed_graph<dlib::bayes_node>::kernel_1a_c* _bn;
	dlib::bayesian_network_join_tree* _bn_current_solution;

public:
	BBN_Plot(const CL_String&);

	void clone_results(BBN_Plot*);
	virtual ~BBN_Plot();
	BBN_Decision* get_decision(const CL_String &);
	BBN_Option* get_option(const CL_String &);
  dlib::directed_graph<dlib::bayes_node>::kernel_1a_c* get_bn();
  BBN_Option* query_result(CL_String option_name);
  dlib::bayesian_network_join_tree* get_bn_current_solution();
  CL_String get_name();
  std::vector<BBN_Decision*>* get_decisions(void);
	void set_name(CL_String new_name);
	void add_decision(BBN_Decision* decision);
	void prepare_bn();
	long decisions_count();
	void update_bn_solution();
	bool set_result(const CL_String&, const CL_String&);
	void clear_bn(void);
	CL_String get_file_name(void);
	unsigned long get_next_decision_id(void); //TODO: Make friend method.

};

#endif
