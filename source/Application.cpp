/*
 * App.cpp
 *
 *  Created on: 29 Dec 2009
 *      Author: greg
 */

#include "Application.h"
#include "main_menu/MainMenu.h"
#include "misc/logging.h"
#include <ClanLib/core.h>
#include <ClanLib/sound.h>
#include <ClanLib/mikmod.h>
#include <ClanLib/vorbis.h>

Application::Application()
{
  Application::log(LOG_LEVEL_DEBUG, "Application constructor called.");
}

Application::~Application()
{
  Application::log(LOG_LEVEL_DEBUG, "Application destructor called.");
}

int Application::main(const std::vector<CL_String> &args)
{
  try
  {
    Application::log(LOG_LEVEL_INFO, "Starting game...");

    // Open the log file
    CL_FileLogger file_logger("game.log");
    file_logger.enable();

    // Create the window
    Application::log(LOG_LEVEL_DEBUG, "Creating window description...");
    CL_DisplayWindowDescription desc;
    desc.set_title("Mystery Generator");
    desc.set_size(CL_Size(1024, 640), true);

    Application::log(LOG_LEVEL_DEBUG, "Creating game window...");
    CL_DisplayWindow window(desc);

    // Initialize the sound system
    CL_SetupSound setup_sound;

    // Initialize mikmod
    CL_SetupMikMod setup_mikmod;

    // Initialize vorbis
    CL_SetupVorbis setup_vorbis;

    // Create world
    Application::log(LOG_LEVEL_DEBUG, "Creating world...");
    MainMenu menu(window);

    // Run the main loop
    Application::log(LOG_LEVEL_DEBUG, "Executing game loop.");
    menu.run();
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

/**
 * Outputs the message to the console and the active log file.
 */
void Application::log(const int level,const CL_String& message)
{
  if(level <= logging_level)
  {
    //Output to Clan lib console and log file
    CL_Console::write_line(message);
    switch(level)
    {
      case LOG_LEVEL_INFO:
        cl_log_event("information",message);
        break;
      case LOG_LEVEL_DEBUG:
        cl_log_event("debug",message);
        break;
      default:
        cl_log_event("[unknown_logging_level]", message);
    };
  }
}
