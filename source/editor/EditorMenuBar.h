/**
 * @file EditorMenuBar.h
 *
 * Created on: 17 Feb 2010
 *  
 * @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef EDITORMENUBAR_H_
#define EDITORMENUBAR_H_

#include <ClanLib/core.h>
#include <ClanLib/gui.h>

class Editor;

class EditorMenuBar : public CL_MenuBar
{
public:
  EditorMenuBar(CL_GUIComponent*, Editor*);
  virtual ~EditorMenuBar();
private:
  CL_PopupMenu menu_file;
  CL_PopupMenu menu_edit;
};

#endif /* EDITORMENUBAR_H_ */
