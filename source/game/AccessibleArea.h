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

class AccessibleArea
{
public:
  AccessibleArea(Scene*);
  virtual ~AccessibleArea();
  void draw();
private:
  Scene* scene;
  std::list<CL_Pointd> points;
};

#endif /* ACCESSIBLEAREA_H_ */
