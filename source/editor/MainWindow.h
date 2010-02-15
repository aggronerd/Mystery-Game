/*
 * mainWindow.h
 *
 *  Created on: 12 Feb 2010
 *      Author: greg
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "dlib/gui_widgets.h"
#include <sstream>
#include <string>
#include "dlib/directed_graph.h"
#include "dlib/string.h"
#include "dlib/bayes_utils.h"
#include "dlib/smart_pointers.h"
#include "dlib/set.h"
#include "dlib/graph_utils.h"
#include "dlib/stl_checked.h"

typedef directed_graph<bayes_node>::kernel_1a_c directed_graph_type;
typedef directed_graph<bayes_node>::kernel_1a_c::node_type node_type;
typedef graph<dlib::set<unsigned long>::compare_1b_c, dlib::set<unsigned long>::compare_1b_c>::kernel_1a_c join_tree_type;

using namespace std;
using namespace dlib;
using namespace dlib::bayes_node_utils;

class MainWindow : public drawable_window
{
    /*!
        INITIAL VALUE
            This window starts out hidden and with an empty Bayesian Network

        WHAT THIS OBJECT REPRESENTS
            This object is the main window of a utility for drawing Bayesian Networks.
            It allows you to draw a directed graph and to set the conditional probability
            tables up for each node in the network.  It also allows you to compute the
            posterior probability of each node.  And finally, it lets you save and load
            networks from file
    !*/
public:
    MainWindow();
    ~MainWindow();

private:

    // Private helper methods

    void initialize_node_cpt_if_necessary ( unsigned long index );
    void load_selected_node_tables_into_cpt_grid ();
    void load_selected_node_tables_into_ppt_grid ();
    void no_node_selected ();


    // Event handlers

    void on_cpt_grid_modified(unsigned long row, unsigned long col);
    void on_evidence_toggled ();
    void on_graph_modified ();
    void on_menu_file_open ();
    void on_menu_file_quit ();
    void on_menu_file_save ();
    void on_menu_file_save_as ();
    void on_menu_help_about ();
    void on_menu_help_help ();
    void on_node_deleted ();
    void on_node_deselected ( unsigned long n );
    void on_node_selected (unsigned long n);
    void on_open_file_selected ( const std::string& file_name);
    void on_save_file_selected ( const std::string& file_name);
    void on_sel_node_evidence_modified ();
    void on_sel_node_num_values_modified ();
    void on_sel_node_text_modified ();
    void on_window_resized ();
    void recalculate_probabilities ();

    // Member data

    const rgb_pixel color_non_evidence;
    const rgb_pixel color_default_bg;
    const rgb_pixel color_evidence;
    const rgb_pixel color_error;
    const rgb_pixel color_gray;
    bool graph_modified_since_last_recalc;

    button btn_calculate;
    check_box sel_node_is_evidence;
    directed_graph_drawer<directed_graph_type> graph_drawer;
    label sel_node_index;
    label sel_node_num_values_label;
    label sel_node_text_label;
    label sel_node_evidence_label;
    menu_bar mbar;
    named_rectangle selected_node_rect;
    tabbed_display tables;
    text_field sel_node_num_values;
    text_field sel_node_text;
    text_field sel_node_evidence;
    text_grid cpt_grid;
    text_grid ppt_grid;
    unsigned long selected_node_index;
    bool node_is_selected;
    widget_group cpt_group;
    widget_group ppt_group;

    scoped_ptr<bayesian_network_join_tree> solution;
    join_tree_type join_tree;
    // The std_vector_c is an object identical to the std::vector except that it checks
    // all its preconditions and throws a dlib::fatal_error if they are violated.
    std_vector_c<assignment> cpt_grid_assignments;
    std::string graph_file_name;
};

#endif /* MAINWINDOW_H_ */
