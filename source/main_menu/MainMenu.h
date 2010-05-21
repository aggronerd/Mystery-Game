/**
 * @file MainMenu.h
 *
 *  Created on: 15 Feb 2010
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef MAINMENU_H_
#define MAINMENU_H_

#include <ClanLib/display.h>
#include <ClanLib/core.h>
#include <ClanLib/gui.h>
#include "../ApplicationModule.h"

class MainMenu : public ApplicationModule
{
  public:
    MainMenu(const CL_DisplayWindow &);
    virtual ~MainMenu();
  private:
    virtual void draw(void);
    //virtual void update(void);
    //virtual void wm_repaint(void);
    bool on_quit(void);
    void on_clicked_button_mystery_generator(void);
    void on_clicked_button_monster_generator(void);
    void on_clicked_button_editor(void);
    CL_Image background_image;
    CL_ResourceManager menu_rm;
    CL_PushButton* button_mystery;
    CL_PushButton* button_monster;
    CL_Window* menu_window;
};

#endif /* MAINMENU_H_ */
