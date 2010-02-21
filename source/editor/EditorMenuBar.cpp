/**
 * @file EditorMenuBar.cpp
 *
 * Created on: 17 Feb 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "EditorMenuBar.h"
#include "Editor.h"
#include "../misc/logging.h"

/**
 * Adds item to itself to represent the menubar component of the editor.
 */
EditorMenuBar::EditorMenuBar(CL_GUIComponent* parent, Editor* editor) : CL_MenuBar(parent)
{
  DEBUG_MSG("EditorMenuBar::EditorMenuBar(CL_GUIComponent*, Editor*) - Called.")

  this->set_geometry(CL_Rect(0, 0, parent->get_width(), 25));

  //Create the file menu.
  menu_file.insert_item("New").func_clicked().set(editor, &Editor::on_menu_new_clicked);
  menu_file.insert_item("Open").func_clicked().set(editor, &Editor::on_menu_open_clicked);
  menu_file.insert_item("Save").func_clicked().set(editor, &Editor::on_menu_save_clicked);
  menu_file.insert_item("Exit").func_clicked().set(editor, &Editor::on_menu_exit_clicked);
  this->add_menu("File", menu_file);

  //Create the edit menu.
  menu_edit.insert_item("Cut").func_clicked().set(editor, &Editor::on_menu_cut_clicked);
  menu_edit.insert_item("Copy").func_clicked().set(editor, &Editor::on_menu_copy_clicked);
  menu_edit.insert_item("Paste").func_clicked().set(editor, &Editor::on_menu_paste_clicked);
  this->add_menu("Edit", menu_edit);
}

EditorMenuBar::~EditorMenuBar()
{}
