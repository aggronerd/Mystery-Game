/*
 * Logger.h
 *
 *  Created on: 14 Jan 2010
 *      Author: greg
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#define LEVEL_DEBUG 0 // Lowest level messages
#define LEVEL_INFO  5 // High level messages

#include <ClanLib/core.h>

/**
 * Basic class for logging messages in the game.
 */
class Logger
{
private:
  static int level;
  static CL_FileLogger file_logger("game.log");
public:
  Logger();
  virtual ~Logger();
  static void setLevel(int);
  static int getLevel(void);
  static void log(const int, const CL_StringRef&);
};

#endif /* LOGGER_H_ */
