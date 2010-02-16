/*
 * MainMenu.h
 *
 *  Created on: 15 Feb 2010
 *      Author: greg
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
    MainMenu(CL_DisplayWindow &);
    virtual ~MainMenu();
  private:
    void draw(void);
    void update(void);
    void wm_repaint(void);
    bool on_quit(void);
    void on_clicked_button_new_game(void);
    void on_clicked_button_editor(void);
    CL_Image background_image;
    //The order of the following is important
    CL_ResourceManager menu_rm;
    CL_DisplayWindow window;
    CL_GUIThemeDefault gui_theme;
    CL_ResourceManager gui_rm;
    CL_GUIWindowManagerTexture wm;
    CL_GUIManager gui;

    CL_PushButton* button_new_game;
    CL_PushButton* button_editor;
    CL_PushButton* button_options;
    CL_Window* menu_window;
};

#endif /* MAINMENU_H_ */
