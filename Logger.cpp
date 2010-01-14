/*
 * Logger.cpp
 *
 *  Created on: 14 Jan 2010
 *      Author: greg
 */

#include "Logger.h"

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
void Logger::setLevel(new_level)
{
  level = new_level;
}

/**
 * Outputs logging message.
 *
 * @param level The level of the message 0 being debug 5 being infomation.
 * @param message The message as a string.
 */
void Logger::Log(int level, const char* message)
{

}
