/*
 * BBN_Info.h
 *
 *  Created on: 22 May 2010
 *      Author: greg
 */

#ifndef BBN_INFO_H_
#define BBN_INFO_H_

#include <ClanLib/gui.h>
#include <ClanLib/core.h>

#define BBN_INFO_LIST_UNDEF "[undefined]"

class BBN_Plot;

/**
 * Displays info on a Bayes Belief network object.
 */
class BBN_Info : public CL_Frame
{
	public:
		BBN_Info(CL_GUIComponent*, BBN_Plot*);
		virtual ~BBN_Info();
	protected:
		BBN_Plot* _bbn_network;

		/*
		 * GUI components
		 */
		CL_ListView* _list;
		CL_PushButton* _button_generate;
		CL_PushButton* _button_set_value;
		CL_ComboBox* _combo_options;
		CL_PopupMenu _selected_options;

		void disable_selection_controls(void);
		void draw_controls(void);
		void clear_controls(void);
		void generate_selected(CL_PushButton*);
		void set_selected(CL_PushButton*);
		void on_selection_changed(CL_ListViewSelection, CL_ListView*);
};

#endif /* BBN_INFO_H_ */
