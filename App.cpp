/*
 * App.cpp
 *
 *  Created on: 29 Dec 2009
 *      Author: greg
 */

#include "App.h"
#include "World.h"
#include <ClanLib/core.h>
#include <ClanLib/sound.h>

int Application::main(const std::vector<CL_String> &args)
{
  try
  {
    Application::logger.log(5, "Application object instantiated.");
    Application::logger.log(0, "Creating window description.");

    // Create the window
    CL_DisplayWindowDescription desc;
    desc.set_title("Mystery Generator");
    desc.set_size(CL_Size(800, 600), true);

    Application::logger.log(0, "Creating game window...");
    CL_DisplayWindow window(desc);
    //CL_SoundOutput output(44100);

    // Create world
    Application::logger.log(0,"Creating world...");
    World world(window);

    // Run the main loop
    Application::logger.log(0,"Executing game loop.");
    world.run();
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
