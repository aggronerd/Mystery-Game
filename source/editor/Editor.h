/*
 * Editor.h
 *
 *  Created on: 15 Feb 2010
 *      Author: greg
 */

#ifndef EDITOR_H_
#define EDITOR_H_

#include <ClanLib/display.h>
#include <ClanLib/core.h>

/**
 * The editor class is used to edit the plot Baysian Networks.
 */
class Editor
{
  public:
    Editor(CL_DisplayWindow &);
    virtual ~Editor();

    int run();

    CL_GraphicContext* getGC(void);

  private:
    //The main graphics context:
    CL_GraphicContext gc;
    //The window object:
    CL_DisplayWindow window;
    //If is false the main loop exits.
    bool quit;

};

#endif /* EDITOR_H_ */
