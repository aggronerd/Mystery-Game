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
#include "../ApplicationModule.h"

class MainMenu : public ApplicationModule
{
  public:
    MainMenu(CL_DisplayWindow &);
    virtual ~MainMenu();
  private:
    void draw(void);
    void update(void);
    CL_Image background_image;
    CL_ResourceManager rm;
};

#endif /* MAINMENU_H_ */
