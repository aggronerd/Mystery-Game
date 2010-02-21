/**
 * @file DecisionsComponent.h
 *
 * Created on: 21 Feb 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef DECISIONSCOMPONENT_H_
#define DECISIONSCOMPONENT_H_

#include <ClanLib/gui.h>

#define DC_BORDER_SIZE 20.0f

class Decisions;

class DecisionsComponent : public CL_GUIComponent
{
public:
  DecisionsComponent(const Decisions*, CL_GUIComponent*);
  virtual ~DecisionsComponent();
private:
  const Decisions* m_decisions;
  CL_PushButton* add_decision_button;
  void on_add_decision_button_clicked(void);
  void on_render(CL_GraphicContext &, const CL_Rect &);
};

#endif /* DECISIONSCOMPONENT_H_ */
