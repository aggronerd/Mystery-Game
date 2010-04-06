/**
 * @file Room.h
 *
 * Created on: 4 Apr 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef ROOM_H_
#define ROOM_H_

#include "Overlay.h"
#include <ClanLib/core.h>
#include <vector>

class Room : public Overlay
{
public:
  Room(World*);
  virtual ~Room();
  void draw(void);
private:
  std::vector<CL_Pointd> corners;
};

#endif /* ROOM_H_ */
