/**
 * @file GameObject.cpp
 *
 *  Created on: 25 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "GameObject.h"
#include "World.h"
#include <ClanLib/core.h>
#include "../misc/logging.h"

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
  CL_Point screen_position;

  //Calculate where the sprite will be drawn on the screen.
  screen_position = world->get_active_viewport()->get_screen_position(world_position);

  //Setup a rectangle so the origin of the spite centres on the bottom.
  CL_Rectf dest(static_cast<float>(screen_position.x - (static_current->get_width()/2)),
                static_cast<float>(screen_position.y - (static_current->get_height())), static_cast<CL_Sizef>(static_current->get_size()));

  CL_Draw::box(*(world->get_gc()),dest,CL_Colorf(1.0f,0.0f,0.0f));

  if(static_current != 0x0)
    static_current->draw(*(world->get_gc()), dest);
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
void GameObject::set_direction(CL_Angle new_direction)
{
  float angle;

  direction = new_direction;
  angle = new_direction.to_degrees();

  //Update the pointer to the current static sprite.
  //TODO: Adjust angles to enable more realistic rotation. Currently scaling of the y axis in the isometric system causes the percieved angle of the body to be different from the percieved angle of the direction.
  if(angle > 337.5 || angle <= 22.5)
    static_current = static_sprites[SPRITE_NW];
  if(angle > 22.5  && angle <= 65.7)
    static_current = static_sprites[SPRITE_N];
  if(angle > 65.7  && angle <= 112.5)
    static_current = static_sprites[SPRITE_NE];
  if(angle > 112.5 && angle <= 157.5)
    static_current = static_sprites[SPRITE_E];
  if(angle > 157.5 && angle <= 202.5)
    static_current = static_sprites[SPRITE_SE];
  if(angle > 202.5 && angle <= 247.5)
    static_current = static_sprites[SPRITE_S];
  if(angle > 247.5 && angle <= 292.5)
    static_current = static_sprites[SPRITE_SW];
  if(angle > 292.5 && angle <= 337.5)
    static_current = static_sprites[SPRITE_W];
}

/**
 * Returns the angle.
 */
CL_Angle GameObject::get_direction(void)
{
  return(direction);
}

/**
 * Sets the world position of the object.
 *
 * param new_position The position as CL_Pointd in terms of world co-ordinates.
 */
void GameObject::set_position(CL_Pointd position)
{
  world_position = position;
}

/**
 * Returns the position in world co-ordinates in CL_Pointd.
 */
CL_Pointd GameObject::get_position()
{
  return(world_position);
}

/**
 * Set the game object to face the vector provided.
 *
 * Vector must be world co-ordinates.
 */
void GameObject::set_facing(CL_Vec2<double> vector)
{
  DEBUG_MSG("GameObject::set_facing(CL_Vec2<double>) - Called - vector = (" + CL_StringHelp::double_to_text(vector.x) + "," + CL_StringHelp::double_to_text(vector.y) + ")")

  //Translate vector to use object's position as origin
  vector = vector - static_cast<CL_Vec2<double> >(get_position());

  //Calculate angle between the vector and a unit vector for the y axis.
  CL_Angle new_direction = CL_Pointd(0,1).angle(vector);

  //Determines if the direction of the angle.
  if(vector.x < 0)
    new_direction = CL_Angle(360,cl_degrees) - new_direction;

  DEBUG_MSG("GameObject::set_facing(CL_Vec2<double>) - new_direction.to_degrees() = " + CL_StringHelp::float_to_text(new_direction.to_degrees()))

  set_direction(new_direction);
}
