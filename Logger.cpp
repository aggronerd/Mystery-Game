/*
 * Logger.cpp
 *
 *  Created on: 14 Jan 2010
 *      Author: greg
 */

#include "Logger.h"
#include <ClanLib/core.h>

Logger::Logger()
{
  //Set info level as default.
  level = LEVEL_INFO;
  file_logger.enable();
}

Logger::~Logger()
{
  //Disable the file logger on close.
  file_logger.disable();
}

/**
 * Returns the min level for logging messages.
 */
int Logger::getLevel()
{
  return(level);
}

/**
 * Set the minimum message level.
 */
void Logger::setLevel(int new_level)
{
  level = new_level;
}

/**
 * Outputs logging message.
 *
 * @param level The level of the message 0 being debug 5 being infomation.
 * @param message The message as a string.
 */
void Logger::log(const int message_level, const CL_StringRef &message)
{

}
