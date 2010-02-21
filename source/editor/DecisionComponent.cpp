/**
 * @file DecisionComponent.cpp
 *
 * Created on: 18 Feb 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "DecisionComponent.h"
#include "../misc/logging.h"
#include "../mystery_xml/Option.h"

DecisionComponent::DecisionComponent(const Decision *decision, CL_GUIComponent *parent) : CL_Window(parent,CL_DisplayWindowDescription()), m_decision(decision)
{
  DEBUG_MSG("DecisionComponent::DecisionComponent(const Decision *, const CL_GUIComponent *) - Called.")

  //Set own geometry
  set_geometry(CL_Rect(0,50,100,300));
  set_draggable(true);

  //Edit box for the name field.
  name_component = new CL_LineEdit(this);
  name_component->set_text("New");
  name_component->set_geometry(get_geometry().set_height(0));

}

DecisionComponent::~DecisionComponent()
{
  DEBUG_MSG("DecisionComponent::~DecisionComponent() - Called.")
  delete name_component;
}
