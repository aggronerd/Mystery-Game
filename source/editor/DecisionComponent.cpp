/**
 * @file DecisionComponent.cpp
 *
 * Created on: 18 Feb 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "DecisionComponent.h"
#include "../misc/logging.h"

DecisionComponent::DecisionComponent(CL_GUIComponent *parent, const Decision* decision) : CL_GUIComponent(parent), m_decision(decision)
{
  DEBUG_MSG("DecisionComponent::DecisionComponent(const CL_GUIComponent*, const Decision*) - Called.")

  //Set own geometry
  set_geometry(CL_Rect(0,0,50,50));

  //Edit box for the name field.
  name_component = new CL_LineEdit(this);
  name_component->set_text("New");
  name_component->set_geometry(get_geometry());
}

DecisionComponent::~DecisionComponent()
{
  DEBUG_MSG("DecisionComponent::~DecisionComponent() - Called.")
  delete name_component;
}

void DecisionComponent::on_render(CL_GraphicContext &gc, const CL_Rect &clip_rect)
{}

void DecisionComponent::on_process_message(const CL_GUIMessage &message)
{}
