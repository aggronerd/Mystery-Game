/**
 * @file Editor.h
 *
 *  Created on: 15 Feb 2010
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef EDITOR_H_
#define EDITOR_H_

#include <ClanLib/display.h>
#include <ClanLib/core.h>
#include "../ApplicationModule.h"

class EditorMenuBar;

/**
 * The editor class is used to edit the plot Baysian Networks.
 */
class Editor : public ApplicationModule
{
  public:
    Editor(const CL_DisplayWindow &);
    virtual ~Editor();
    void on_menu_new_clicked(void);
    void on_menu_open_clicked(void);
    void on_menu_save_clicked(void);
    void on_menu_exit_clicked(void);
    void on_menu_cut_clicked(void);
    void on_menu_copy_clicked(void);
    void on_menu_paste_clicked(void);
  private:
    void draw(void);
    void update(void);
    EditorMenuBar* menu_bar;
    CL_Window* main_window;
};

#endif /* EDITOR_H_ */
