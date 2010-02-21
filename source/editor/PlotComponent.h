/**
 * @file PlotComponent.h
 *
 * Created on: 21 Feb 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef PLOTCOMPONENT_H_
#define PLOTCOMPONENT_H_

#include <ClanLib/gui.h>

class DecisionsComponent;
class Plot;

/**
 * This class is used to represent a GUI component version of a
 * Plot class. When instantiated it is displayed inside the parent
 * CL_GUIComponent. It inherits all the methods of a Plot class
 * as well as CL_GUIComponent.
 */
class PlotComponent : public CL_GUIComponent
{
public:
  PlotComponent(Plot*, CL_GUIComponent*);
  virtual ~PlotComponent();
private:
  const Plot* m_plot; //TODO: Don't forget to destroy me elsewhere
  DecisionsComponent* decisions_component;
};

#endif /* PLOTCOMPONENT_H_ */
