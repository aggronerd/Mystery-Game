/*
 * Console.h
 *
 *  Created on: 13 Jan 2010
 *      Author: greg
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "Overlay.h"

class World;

class Console : public Overlay
{
public:
  Console(World*);
  virtual ~Console();
  void draw();
};

#endif /* CONSOLE_H_ */
