/**
 * @file Viewport.h
 *
 * Created on: 31 Mar 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include <ClanLib/core.h>

#define VIEWPOINT_Y_SCALE 0.5
#define VIEWPOINT_ZOOM 45.254834 // 64 pixel width of tile. sqrt((64*64)/2)
#define VIEWPOINT_SCROLL_DISTANCE_PER_SEC 10
#define VIEWPOINT_SCROLL_BORDER_WIDTH 40

class Scene;

/**
 * A Viewport is used to translate what is in the world and determine
 * what and what not to render on the player's screen.
 */
class Viewport
{
public:
  Viewport(Scene*);
  virtual ~Viewport();
  CL_Point get_screen_position(const CL_Pointd&);
  CL_Pointd get_world_position(CL_Point);
  bool get_is_visible(const CL_Pointd&);
  void center_on_world(const CL_Pointd&);
  void update(unsigned int);
  void set_scroll_w(bool);
  void set_scroll_e(bool);
  void set_scroll_s(bool);
  void set_scroll_n(bool);
  void set_enable_scrolling(bool);
protected:
  Scene* scene;
  /**
   * The origin of the viewport in the world system.
   */
  CL_Pointd origin;
  /**
   * The center of the screen in screen co-ordinates system.
   */
  CL_Point screen_center;
  bool enable_scrolling;
  bool scroll_w;
  bool scroll_e;
  bool scroll_s;
  bool scroll_n;
};

#endif /* VIEWPORT_H_ */
