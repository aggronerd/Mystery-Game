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
    // Create the window
    CL_DisplayWindowDescription desc;
    desc.set_title("Mystery Generator");
    desc.set_size(CL_Size(1024, 768), true);

    CL_DisplayWindow window(desc);
    //CL_SoundOutput output(44100);

    // Create world
    World world(window);

    // Run the main loop
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
