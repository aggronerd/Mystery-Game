/**
 * @file logging.h
 *
 *  Contains pre-processor macros for logging. If LOG_DEBUG_MESSAGES
 *  is not defined then the code isn't compiled into the application.
 *
 *  Created on: 16 Jan 2010
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef CORE_H_
#define CORE_H_

  #define LOG_LEVEL_DEBUG 5
  #define LOG_LEVEL_WARN 2
  #define LOG_LEVEL_INFO 0

  //Comment out to disable debug messages being called.
  //#define LOG_DEBUG_MESSAGES

  #ifdef LOG_DEBUG_MESSAGES
    #include <ClanLib/core.h>
    #include "../Application.h"
#define DEBUG_MSG(message) Application::log(LOG_LEVEL_DEBUG,CL_String8(__FILE__) + CL_String8(":") + CL_StringHelp::int_to_text(__LINE__) + CL_String8(" - ") + CL_String8(message));
  #else
    #define DEBUG_MSG(message)
  #endif /* LOG_DEBUG_MESSAGES */

#endif /* CORE_H_ */
