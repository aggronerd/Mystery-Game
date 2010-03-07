/**
 * @file PlotComponent.cpp
 *
 * Created on: 21 Feb 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "PlotComponent.h"
#include "../mystery_xml/Plot.h"
#include "DecisionsComponent.h"
#include "../misc/logging.h"
#include <ClanLib/core.h>

PlotComponent::PlotComponent(Plot* plot, CL_GUIComponent* parent) : CL_GUIComponent(parent)
{
  DEBUG_MSG("PlotComponent::PlotComponent(Plot*, CL_GUIComponent*) - Called.")

  m_plot = plot;

 // set_c

  //Create the decisions_component
  //decisions_component = new DecisionsComponent(plot->get_root_decisions(), this);

}

PlotComponent::~PlotComponent()
{
  DEBUG_MSG("PlotComponent::~PlotComponent() - Called.")
  delete decisions_component;
}
