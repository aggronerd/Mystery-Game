/**
 * @file App.cpp
 *
 *  Created on: 29 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#include "Application.h"
#include "main_menu/MainMenu.h"
#include "game/World.h"
#include "monster_generator_demo/MonsterGeneratorDemo.h"
#include "misc/logging.h"
#include "ApplicationModuleExitCode.h"
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

int Application::main(const std::vector<CL_String8> &args)
{
  try
  {
    Application::log(LOG_LEVEL_INFO, "Starting game...");

    // Open the log file
    //CL_FileLogger file_logger("game.log");
    //file_logger.enable();

    // Create the window
    CL_DisplayWindowDescription desc;
    desc.set_title("Bayes Network Random Generator");
    desc.set_size(CL_Size(1024, 600), true);
    desc.set_fullscreen(false);

    CL_DisplayWindow window(desc);

    // Initialize the sound system
    CL_SetupSound setup_sound;
    CL_SetupMikMod setup_mikmod;
    CL_SetupVorbis setup_vorbis;

    //Run the loop for the modules of the game.
    ApplicationModuleExitCode response = EXIT_MODULE_AND_LOAD_MAIN_MENU;
    ApplicationModule* mod = 0x0;
    do {
      switch(response)
      {
        case EXIT_MODULE_AND_LOAD_MYSTERY_GENERATOR:
          mod = (ApplicationModule*)new World(window);
          break;
        case EXIT_MODULE_AND_LOAD_MONSTER_GENERATOR:
          mod = (ApplicationModule*)new MonsterGeneratorDemo(window);
          break;
        case EXIT_MODULE_AND_LOAD_MAIN_MENU:
          mod = (ApplicationModule*)new MainMenu(window);
          break;
        default:
          throw CL_Exception("Not supposed to happen");//TODO: Raise an error here
      }
      response = mod->run();
      //TODO: Ensure does not cause leak because call is to destroy general class not decenants.
      delete mod;
    } while (response != EXIT_APPLICATION);

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
void Application::log(const int level,const CL_String8& message)
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
