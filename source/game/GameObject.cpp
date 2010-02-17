/**
 * @file GameObject.cpp
 *
 *  Created on: 25 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
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
  for(int i = 0; i < 8; i++)
    static_sprites[i] = 0x0;
  static_current = 0x0;

  this->set_position(initial_position);
  this->set_direction(initial_direction);
}

GameObject::~GameObject()
{
  world = 0;
  //Destroy sprites which have been declared.
  for(int i = 0; i < 8; i++)
    delete static_sprites[i];
}

/**
 * Draws the current static sprite for the object.
 */
void GameObject::draw()
{
  if(static_current != 0x0)
    static_current->draw(*(world->get_gc()),(float)position.x,(float)position.y);
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
void GameObject::set_direction(CL_Angle& new_direction)
{
  float angle;

  direction = new_direction;
  angle = new_direction.to_degrees();

  //Update the pointer to the current static sprite.
  if(angle > 337.5 || angle <= 22.5)
    static_current = static_sprites[SPRITE_N];
  if(angle > 22.5  && angle <= 65.7)
    static_current = static_sprites[SPRITE_NE];
  if(angle > 65.7  && angle <= 112.5)
    static_current = static_sprites[SPRITE_E];
  if(angle > 112.5 && angle <= 157.5)
    static_current = static_sprites[SPRITE_SE];
  if(angle > 157.5 && angle <= 202.5)
    static_current = static_sprites[SPRITE_S];
  if(angle > 202.5 && angle <= 247.5)
    static_current = static_sprites[SPRITE_SW];
  if(angle > 247.5 && angle <= 292.5)
    static_current = static_sprites[SPRITE_W];
  if(angle > 292.5 && angle <= 337.5)
    static_current = static_sprites[SPRITE_NW];
}

/**
 * Returns the angle.
 */
CL_Angle GameObject::get_direction(void)
{
  return(direction);
}

/**
 * Sets the position of the object.
 *
 * param new_position The position as CL_Pointd in terms of world co-ordinates.
 */
void GameObject::set_position(CL_Pointd& new_position)
{
  position = IsometricConversions::world_to_isometric(new_position);
}

/**
 * Returns the position in world co-ordinates in CL_Pointd.
 */
CL_Pointd GameObject::get_position()
{
  return(IsometricConversions::isometric_to_world(position));
}
