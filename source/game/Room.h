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
  Room(Scene*,const CL_String&, double, double, double, double);
  virtual ~Room();
  virtual void draw(void);
  CL_String getName(void);
protected:
  CL_String _name;
};

#endif /* ROOM_H_ */
