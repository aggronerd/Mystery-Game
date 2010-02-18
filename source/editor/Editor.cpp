/**
 * @file Editor.cpp
 *
 *  Created on: 15 Feb 2010
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "Editor.h"
#include "EditorMenuBar.h"
#include "DecisionComponent.h"
#include "../misc/logging.h"
#include "../mystery_xml/Plot.h"
#include "../mystery_xml/Decisions.h"

Editor::Editor(const CL_DisplayWindow &display_window) : ApplicationModule(display_window)
{
  DEBUG_MSG("Editor::Editor(CL_DisplayWindow &) - Called.")

  //Create the main window which wraps the whole screen
  CL_GUITopLevelDescription desc;
  desc.set_allow_resize(false);
  desc.set_decorations(false);
  desc.set_size(window.get_geometry().get_size(),true);
  desc.set_title("Plot Editor");
  main_window = new CL_Window(&gui,desc);

  //Add the menubar
  menu_bar = new EditorMenuBar(main_window, this);

  //Loads a new plot into memory.
  active_plot = new Plot();

}

Editor::~Editor()
{
  DEBUG_MSG("Editor::~Editor() - Called.")

  delete menu_bar;
  delete main_window;

  if(active_plot!=0x0)
    delete active_plot;

  // decision components are destroyed by the
  // GUI manager when the window is destroyed.
}

/**
 * Draws the GUI.
 */
void Editor::draw()
{
  gc.clear(CL_Colorf(0.0f,0.0f,0.0f));

  //Process GUI
  gui.exec(false);
  wm.draw_windows(gc);

  window.flip(1);
}

/**
 * Updates logic.
 */
void Editor::update()
{
  //Nothing needs updating.
}

/**
 * Creates a new Plot object.
 */
void Editor::on_menu_new_clicked()
{
  //Got to delete the open one from memory first!
  if(active_plot!=0x0)
    delete active_plot;
  active_plot = new Plot();
}

void Editor::on_menu_open_clicked()
{

}

void Editor::on_menu_save_clicked()
{

}

/*
 * Tells the loop to stop and return to the main menu.
 */
void Editor::on_menu_exit_clicked()
{
  exit_code = EXIT_MODULE_AND_LOAD_MAIN_MENU;
}

void Editor::on_menu_cut_clicked()
{

}

void Editor::on_menu_copy_clicked()
{

}

void Editor::on_menu_paste_clicked()
{

}

/**
 * Adds a new decision object to the structure.
 */
void Editor::on_menu_add_decision()
{
  //Create the object.
  Decision* new_decision = new Decision(active_plot);
  //Attach to the structure.
  active_plot->get_root_decisions()->add_decision(new_decision);
  //Attach to a new GUI component.
  decision_components.push_back(new DecisionComponent(main_window,new_decision));
}
