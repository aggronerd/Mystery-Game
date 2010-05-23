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

class BBN_Plot;

/**
 * Displays info on a Bayes Belief network object.
 */
class BBN_Info : public CL_Window
{
	public:
		BBN_Info(CL_GUIManager*, const CL_GUITopLevelDescription&, BBN_Plot*);
		virtual ~BBN_Info();
	protected:
		BBN_Plot* _bbn_network;
		CL_ListView* _list;
		void draw_controls(void);
		void clear_controls(void);
};

#endif /* BBN_INFO_H_ */
