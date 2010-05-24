/*
 * BBN_Info.cpp
 *
 *  Created on: 22 May 2010
 *      Author: greg
 */

#include "BBN_Info.h"
#include "BBN_Plot.h"
#include "../misc/logging.h"
#include <vector>
#include "BBN_Decision.h"
#include "BBN_Option.h"
#include "BBN_Exception.h"

BBN_Info::BBN_Info(CL_GUIComponent* owner, BBN_Plot* bbn_network) : CL_GroupBox(owner)
{
	DEBUG_MSG("BBN_Info::BBN_Info(CL_GUIManager*, const char*) - Called.")

	_bbn_network = bbn_network;
	_list = 0x0;
	_button_generate = 0x0;
	_button_set_value = 0x0;
	_combo_options = 0x0;

	func_resized().set(this,&BBN_Info::on_resized);

	draw_controls();
}

BBN_Info::~BBN_Info()
{
	DEBUG_MSG("BBN_Info::~BBN_Info() - Called.")

	clear_controls();
}

/**
 * Clears all existing controls and draws new ones
 * for the active _bnn_network object.
 */
void BBN_Info::draw_controls()
{
	clear_controls();

	//Create the list of decisions.
	_list = new CL_ListView(this);
	_list->set_display_mode(listview_mode_details);
	_list->func_selection_changed().set(this,&BBN_Info::on_selection_changed,_list);

	CL_ListViewItem doc_item = _list->get_document_item();

	//Setup headers.
	CL_ListViewHeader* lv_header = _list->get_header();
	lv_header->append(lv_header->create_column("name_id", "Decision Name"));
	lv_header->append(lv_header->create_column("value_id", "Value"));

	//Itterate through decisions and list values
	std::vector<BBN_Decision*>* decisions = _bbn_network->get_decisions();
	std::vector<BBN_Decision*>::iterator it;
	CL_ListViewItem items[decisions->size()];
	int i = 0;
	for(it = decisions->begin(); it != decisions->end(); ++it)
	{
		items[i] = _list->create_item();
		items[i].set_column_text("name_id", (*it)->get_name());
		if((*it)->has_generated_result())
		{
			//Result has been chosen.
			items[i].set_column_text("value_id", (*it)->get_result()->get_name());
		}
		else
		{
			//Result is undefined.
			items[i].set_column_text("value_id", BBN_INFO_LIST_UNDEF);
		}
		items[i].set_editable(false);

		doc_item.append_child(items[i]);
		i++;
	}

	//Create the "Generate Selected" button
	_button_generate = new CL_PushButton(this);
	_button_generate->set_text("Generate Selected");
	_button_generate->func_clicked().set(this, &BBN_Info::generate_selected, _button_generate);
  _button_generate->set_enabled(false);

  //Create the "Set" button
  _button_set_value = new CL_PushButton(this);
  _button_set_value->set_text("Set");
  _button_set_value->func_clicked().set(this, &BBN_Info::set_selected, _button_set_value);
  _button_set_value->set_enabled(false);

  //Create the options combo box
  _combo_options = new CL_ComboBox(this);
  _combo_options->set_enabled(false);
  _combo_options->set_popup_menu(_selected_options);

  //Call to resize components
  func_resized().invoke();

	decisions = 0x0;
	lv_header = 0x0;

}

/**
 * Enables or disables the buttons based on the currently selected item.
 *
 * @param selection
 * @param listview
 */
void BBN_Info::on_selection_changed(CL_ListViewSelection selection, CL_ListView* listview)
{
	CL_ListViewSelectedItem item = selection.get_first();
	if(!item.is_null())
	{
		if(item.get_item().get_column("value_id").get_text() == BBN_INFO_LIST_UNDEF)
		{
			//Item is selected and it is undefined.
			_button_generate->set_enabled(true);
			_button_set_value->set_enabled(true);

			BBN_Decision* decision = _bbn_network->get_decision(
					item.get_item().get_column("name_id").get_text());

			if(decision != 0x0)
			{
				_selected_options = CL_PopupMenu();

				//Iterate through options and load them into the new menu.
				std::vector<BBN_Option*>::iterator it;
				std::vector<BBN_Option*>* options = decision->get_options();
				for(it = options->begin(); it != options->end(); ++it)
				{
					CL_String option_name = (*it)->get_name();
					_selected_options.insert_item(option_name);
				}

				_combo_options->set_popup_menu(_selected_options);

			}
			else
			{
				throw(BBN_Exception("BBN_Info::on_selection_changed((CL_ListViewSelection, CL_ListView*) - Unrecognised decision selected."));
			}

		}
		else
		{
			_selected_options = CL_PopupMenu();
			_combo_options->set_text("");
			_combo_options->set_popup_menu(_selected_options);
			_combo_options->set_enabled(false);
			_button_generate->set_enabled(false);
			_button_set_value->set_enabled(false);
		}
	}
}

/**
 * Clears controls loaded by this component.
 */
void BBN_Info::clear_controls()
{
	if(_list != 0x0)
	{
		delete(_list);
		_list = 0x0;
	}
	if(_button_generate != 0x0)
	{
		delete(_button_generate);
		_button_set_value = 0x0;
	}
	if(_button_set_value != 0x0)
	{
		delete(_button_set_value);
		_button_set_value = 0x0;
	}
	if(_combo_options != 0x0)
	{
		delete(_combo_options);
		_combo_options = 0x0;
	}
}

/**
 * Determines if there is an item selected in the list and
 * if it refers to a decision in the bayes net which hasn't
 * been generated yet it then proceeds to generate it. Otherwise
 * does nothing.
 *
 * Preconditions:
 * - _list is not null
 * - _bbn_network is not null
 */
void BBN_Info::generate_selected(CL_PushButton* button)
{
	if(_bbn_network != 0x0 && _list != 0x0)
	{

		//Disable controls.
		disable_selection_controls();

		CL_ListViewItem selected = _list->get_selected_item();
		if(!selected.is_null())
		{
			//Attempt to generate
			BBN_Option* option = _bbn_network->query_result(selected.get_column("name_id").get_text());
			if(option != 0x0)
				selected.set_column_text("value_id",option->get_name());
		}
		else
		{
			//Do nothing as nothing is selected.
		}
	}
	else
	{
		throw(BBN_Exception("BBN_Info::generate_selected(CL_InputEvent, CL_PushButton*) - Failed pre-conditions."));
	}
}

/**
 * Sets the value of the selected item on the list it the
 * value of the combo box.
 *
 * Preconditions:
 * - _list is not null
 * - _bbn_network is not null
 * - _combo_options is not null
 * - An item is selected
 *
 * @param button
 */
void BBN_Info::set_selected(CL_PushButton* button)
{
	if(_combo_options != 0x0 && _bbn_network != 0x0 &&
		 _list != 0x0 && !(_list->get_selected_item().is_null()))
	{

		if(_combo_options->get_text() != "")
		{

			//Retrieve the values
			CL_ListViewItem selected = _list->get_selected_item();
			CL_String value = _combo_options->get_text();
			CL_String name = selected.get_column("name_id").get_text();

			//Reset the controls.
			disable_selection_controls();

			//Attempt to set the value
			DEBUG_MSG(CL_String("BBN_Info::set_selected(CL_PushButton*) - Attempting to set the value of '") +
					name + "' to '" + value + "'...")

			if(_bbn_network->set_result(name,value))
			{
				DEBUG_MSG("BBN_Info::set_selected(CL_PushButton*) - Success.")
				//Update the list item.
				selected.set_column_text("value_id",
					_bbn_network->query_result(selected.get_column("name_id").get_text())->get_name());
			}
			else
			{
				DEBUG_MSG("BBN_Info::set_selected(CL_PushButton*) - Failed.")
			}

		}
	}
	else
	{
		throw(BBN_Exception("BBN_Info::set_selected(CL_PushButton*) - Failed pre-conditions."));
	}
}

/**
 * Disables all the controls for changine selected items.
 */
void BBN_Info::disable_selection_controls()
{
	//Set button
	_button_set_value->set_enabled(false);

	//Generate selected button
  _button_generate->set_enabled(false);

	//Options combo box
	_combo_options->set_enabled(false);
	_selected_options = CL_PopupMenu();
	_combo_options->set_popup_menu(_selected_options);
	_combo_options->set_text("");
}

/**
 * Resizes components to fit the area.
 */
void BBN_Info::on_resized()
{
	CL_Rect client_area = CL_Rect(0,0,this->get_width(),this->get_height());

	if(_list != 0x0)
	{
		_list->set_geometry(CL_Rect(client_area.left + 10, client_area.top + 10,
														    client_area.right - 10, client_area.bottom - 50));

		//Resize columns
		CL_ListViewHeader* lv_header = _list->get_header();
		lv_header->get_column("name_id").set_width(_list->get_width()/2);
		lv_header->get_column("value_id").set_width(_list->get_width()/2);
	}

	if(_button_generate != 0x0)
		_button_generate->set_geometry(CL_Rect(client_area.right - 120,
				client_area.bottom - 40, client_area.right - 10, client_area.bottom - 10));

	if(_button_set_value != 0x0)
		_button_set_value->set_geometry(CL_Rect(client_area.right - 205,
			  client_area.bottom - 40, client_area.right - 125, client_area.bottom - 10));

	if(_combo_options != 0x0)
		_combo_options->set_geometry(CL_Rect(client_area.right - 350,
				client_area.bottom - 35, client_area.right - 210, client_area.bottom - 15));
}

/**
 * Returns a pointer to the bayes net currently represented by
 * the control.
 *
 * @return
 */
BBN_Plot* BBN_Info::get_bayes_net()
{
	return(_bbn_network);
}
