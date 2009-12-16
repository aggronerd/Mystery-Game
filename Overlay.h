/*
 * Overlay.h
 *
 *  Created on: 12 Dec 2009
 *      Author: greg
 */

#ifndef OVERLAY_H_
#define OVERLAY_H_

class Game;

class Overlay
{
  public:
    Overlay(Game*);
    virtual ~Overlay();
    virtual void draw()=0;
  protected:
    Game* g;
};

#endif /* OVERLAY_H_ */
