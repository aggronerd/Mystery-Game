#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>

#include <cmath>
#include "Application.h"

// Choose the target renderer
//#define USE_OPENGL_2
//#define USE_OPENGL_1
#define USE_SOFTWARE
//#define USE_SDL

#ifdef USE_SDL
#include <ClanLib/sdl.h>
#endif

#ifdef USE_SOFTWARE
#include <ClanLib/swrender.h>
#endif

#ifdef USE_OPENGL_1
#include <ClanLib/gl1.h>
#endif

#ifdef USE_OPENGL_2
#include <ClanLib/gl.h>
#endif

// This is the Program class that is called by CL_ClanApplication
class Program
{
public:
        static int main(const std::vector<CL_String8> &args)
        {
                // Initialize ClanLib base components
                CL_SetupCore setup_core;

                // Initialize the ClanLib display component
                CL_SetupDisplay setup_display;

#ifdef USE_SDL
                CL_SetupSDL setup_sdl;
#endif

#ifdef USE_SOFTWARE
                CL_SetupSWRender setup_sw;
#endif

#ifdef USE_OPENGL_1
                CL_SetupGL1 setup_gl1;
#endif

#ifdef USE_OPENGL_2
                CL_SetupGL setup_gl;
#endif

                // Start the Application
                Application game;
                int retval = game.main(args);
                return retval;
        }
};

// Instantiate CL_ClanApplication, informing it where the Program is located
CL_ClanApplication app(&Program::main);




