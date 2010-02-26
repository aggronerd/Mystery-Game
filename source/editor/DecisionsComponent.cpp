/**
 * @file DecisionsComponent.cpp
 *
 * Created on: 21 Feb 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "DecisionsComponent.h"
#include "../misc/logging.h"
#include <ClanLib/display.h>

DecisionsComponent::DecisionsComponent(const Decisions* decisions, CL_GUIComponent* parent) : CL_GUIComponent(parent)
{
  DEBUG_MSG("DecisionsComponent::DecisionsComponent(const Decisions*, CL_GUIComponent*) - Called.")

  m_decisions = decisions;

  set_geometry(parent->get_geometry().shrink(DC_BORDER_SIZE));

  //Create the add button which appears in the top right
  add_decision_button = new CL_PushButton(this);
  add_decision_button->set_geometry(CL_Rect(CL_Point(0,0),CL_Size(40,12)));
  add_decision_button->set_text("Add Decision");
  add_decision_button->func_clicked().set(this, &DecisionsComponent::on_add_decision_button_clicked);

  //Apply custom render function to GUI Component
  func_render().set(this, &DecisionsComponent::on_render);
}

DecisionsComponent::~DecisionsComponent()
{
  DEBUG_MSG("DecisionsComponent::~DecisionsComponent() - Called.")
  delete add_decision_button;
}

void DecisionsComponent::on_add_decision_button_clicked(void)
{

}

void DecisionsComponent::on_render(CL_GraphicContext &gc, const CL_Rect &clip_rect)
{
  //Draw the basic box border.
  CL_Draw::box(gc,  get_geometry(), CL_Colorf(1.0f, 0.0f, 0.0f));
}
