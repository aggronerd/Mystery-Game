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

BBN_Info::BBN_Info(CL_GUIManager* manager, const CL_GUITopLevelDescription& desc, BBN_Plot* bbn_network) : CL_Window(manager, desc)
{
	DEBUG_MSG("BBN_Info::BBN_Info(CL_GUIManager*, const char*) - Called.")
	_bbn_network = bbn_network;
	_list = 0x0;
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

	CL_Rect client_area = get_client_area();

	//Create the list of decisions.
	_list = new CL_ListView(this);
	_list->set_geometry(CL_Rect(client_area.left + 10, client_area.top + 10,
							   client_area.right - 10, client_area.bottom - 10));
	_list->set_display_mode(listview_mode_details);

	CL_ListViewItem doc_item = _list->get_document_item();

	//Setup headers.
	CL_ListViewHeader* lv_header = _list->get_header();
	lv_header->append(lv_header->create_column("name_id", "Decision Name")).set_width(130);
	lv_header->append(lv_header->create_column("value_id", "Value")).set_width(130);

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
			items[i].set_column_text("value_id", "[undefined]");
		}
		items[i].set_editable(true);
		items[i].set_icon(1);
		items[i].add_overlay_icon(1001);
		items[i].set_open(false);

		doc_item.append_child(items[i]);
		i++;
	}

	decisions = 0x0;
	lv_header = 0x0;

}

/**
 * Clears controls loaded by this component.
 */
void BBN_Info::clear_controls()
{
	if(_list != 0x0)
		delete(_list);
}
