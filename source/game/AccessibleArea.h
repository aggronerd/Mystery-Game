/**
 * @file AccessibleArea.h
 *
 * Created on: 6 Apr 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef ACCESSIBLEAREA_H_
#define ACCESSIBLEAREA_H_

#include <ClanLib/core.h>
#include <list>

class Scene;

/**
 * Provides areas defined by a series of points and an area
 * where the player's character may walk within, therefore
 * provides rules for collisions. More specific implementations
 * exist such as Room.
 */
class AccessibleArea
{
public:
  AccessibleArea(Scene*, double, double, double, double);
  virtual ~AccessibleArea();
  virtual void draw(void);
protected:
  Scene* scene;
  std::list<CL_Pointd> points;
};

#endif /* ACCESSIBLEAREA_H_ */
