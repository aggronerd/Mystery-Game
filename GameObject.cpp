/*
 * GameObject.cpp
 *
 *  Created on: 25 Dec 2009
 *      Author: greg
 */

#include "GameObject.h"
#include "World.h"
#include "IsometricConversions.h"
#include <ClanLib/core.h>

/**
 *
 * param w World*
 * param initial_position CL_Pointd The starting position in world coordinates.
 * param initial_direction CL_Angle
 */
GameObject::GameObject(World* w, CL_Pointd& initial_position, CL_Angle& initial_direction)
{

  //TODO: add if debug mode.
  cl_log_event("debug","Instance of GameObject created at x=",initial_position.x," y=", initial_position.y, " angle=", initial_direction.to_degrees());

  //Set the world instance variable.
  world = w;

  //Reset pointers to NULL
  static_n =0x0;
  static_ne =0x0;
  static_e =0x0;
  static_se =0x0;
  static_s =0x0;
  static_sw =0x0;
  static_w =0x0;
  static_nw =0x0;
  static_current =0x0;

  this->setPosition(initial_position);
  this->setDirection(initial_direction);
}

GameObject::~GameObject()
{
  world = 0;
  //Destroy sprites which have been declared.
  if(static_n != 0x0)
    delete static_n;
  if(static_ne != 0x0)
    delete static_ne;
  if(static_e != 0x0)
      delete static_e;
  if(static_se != 0x0)
      delete static_se;
  if(static_s != 0x0)
      delete static_s;
  if(static_sw != 0x0)
      delete static_sw;
  if(static_w != 0x0)
      delete static_w;
  if(static_nw != 0x0)
      delete static_nw;
}

/**
 * Draws the current static sprite for the object.
 */
void GameObject::draw()
{
  if(static_current != 0x0)
    static_current->draw(*(world->getGC()),(float)position.x,(float)position.y);
}

/**
 * Updates any animation in the current sprite.
 */
bool GameObject::update(unsigned int time_elapsed_ms)
{
  if(static_current != 0)
    static_current->update(time_elapsed_ms);
  return(true);
}

/**
 * Sets the direction the game object is facing. This effects
 * the sprite which is used when drawing it.
 */
void GameObject::setDirection(CL_Angle& new_direction)
{
  float angle;

  direction = new_direction;
  angle = new_direction.to_degrees();

  //Update the pointer to the current static sprite.
  if(angle > 337.5 || angle <= 22.5)
    static_current = static_n;
  if(angle > 22.5  && angle <= 65.7)
    static_current = static_ne;
  if(angle > 65.7  && angle <= 112.5)
    static_current = static_e;
  if(angle > 112.5 && angle <= 157.5)
    static_current = static_se;
  if(angle > 157.5 && angle <= 202.5)
    static_current = static_s;
  if(angle > 202.5 && angle <= 247.5)
    static_current = static_sw;
  if(angle > 247.5 && angle <= 292.5)
    static_current = static_w;
  if(angle > 292.5 && angle <= 337.5)
    static_current = static_nw;
}

/**
 * Returns the angle.
 */
CL_Angle GameObject::getDirection(void)
{
  return(direction);
}

/**
 * Sets the position of the object.
 *
 * param new_position The position as CL_Pointd in terms of world co-ordinates.
 */
void GameObject::setPosition(CL_Pointd& new_position)
{
  position = IsometricConversions::worldToIsometric(new_position);
}

/**
 * Returns the position in world co-ordinates in CL_Pointd.
 */
CL_Pointd GameObject::getPosition()
{
  return(IsometricConversions::isometricToWorld(position));
}
