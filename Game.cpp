/*
 * Game.cpp
 *
 *  Created on: 6 Dec 2009
 *      Author: greg
 */

#include "Game.h"
#include "IsometricGrid.h"
#include "PlayerCharacter.h"
#include "GameObject.h"
#include "Overlay.h"

Game::Game()
{
}

Game::~Game()
{
  overlays.clear();
  gc = NULL;
  rm = NULL;
}

void Game::addOverlay(Overlay* overlay)
{
  overlays.push_back(overlay);
}

void Game::addGameObject(GameObject* game_object)
{
  game_objects.push_back(game_object);
}

// The start of the Application
int Game::start(const std::vector<CL_String> &args)
{
        quit = false;

        try
        {
                CL_Pointd pc_start(0,0);

                // TODO: Allow the user to set the size of the window.
                CL_DisplayWindow window("Isometric Engine", 1024, 768);

                // Connect the Window close event
                CL_Slot slot_quit = window.sig_window_close().connect(this, &Game::on_window_close);

                // Connect a keyboard handler to on_key_up()
                CL_Slot slot_input_up = (window.get_ic().get_keyboard()).sig_key_up().connect(this, &Game::on_input_up);

                // Get the graphic context
                gc = &window.get_gc();

                //Get the resource manager
                rm = new CL_ResourceManager("resources.xml");

                // Isometric grid overlay
                IsometricGrid grid(this);
                addOverlay(&grid);

                // Add player character
                PlayerCharacter pc(this,pc_start);
                addGameObject(&pc);

                // Run until someone presses escape
                while (!quit)
                {
                        // Clear the display to black.
                        gc->clear(CL_Colorf(0.0f,0.0f,0.0f));

                        // Draw all game objects
                        std::list<GameObject *>::iterator it_go;
                        for(it_go = game_objects.begin(); it_go != game_objects.end(); ++it_go)
                          (*it_go)->draw();

                        // Draw all overlays
                        std::list<Overlay *>::iterator it_ov;
                        for(it_ov = overlays.begin(); it_ov != overlays.end(); ++it_ov)
                          (*it_ov)->draw();

                        // Flip the display, showing on the screen what we have drawed
                        // since last call to flip()
                        window.flip(1);

                        // This call processes user input and other events
                        CL_KeepAlive::process(0);
                }
        }
        catch(CL_Exception &exception)
        {
                // Create a console window for text-output if not available
                CL_ConsoleWindow console("Console", 80, 160);
                CL_Console::write_line("Exception caught: " + exception.get_message_and_stack_trace());
                console.display_close_message();

                return -1;
        }
        return 0;
}

// A key was pressed
void Game::on_input_up(const CL_InputEvent &key, const CL_InputState &state)
{
        if(key.id == CL_KEY_ESCAPE)
        {
                quit = true;
        }
}

// The window was closed
void Game::on_window_close()
{
        quit = true;
}

CL_GraphicContext* Game::getGC()
{
  return(gc);
}

CL_ResourceManager* Game::getRM()
{
  return(rm);
}
