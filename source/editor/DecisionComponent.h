/**
 * @file DecisionComponent.h
 *
 * Created on: 18 Feb 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef PLOTCONTROL_H_
#define PLOTCONTROL_H_

#include <ClanLib/gui.h>
#include "../mystery_xml/Decision.h"

class DecisionComponent : public CL_GUIComponent
{
public:
  DecisionComponent(CL_GUIComponent*,const Decision*);
  virtual ~DecisionComponent();
private:
  void on_render(CL_GraphicContext &, const CL_Rect &);
  void on_process_message(const CL_GUIMessage&);
  const Decision* m_decision;
  CL_LineEdit* name_component;
};

#endif /* PLOTCONTROL_H_ */
