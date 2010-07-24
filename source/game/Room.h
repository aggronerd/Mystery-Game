/**
 * @file Room.h
 *
 * Created on: 4 Apr 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef ROOM_H_
#define ROOM_H_

#include "AccessibleArea.h"

class Room : public AccessibleArea
{
public:
  Room(Scene*,const CL_String8&, double, double, double, double);
  virtual ~Room();
  virtual void draw(void);
  CL_String8 getName(void);
protected:
  CL_String8 _name;
};

#endif /* ROOM_H_ */
