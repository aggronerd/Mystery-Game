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

/**
 * Basic class for logging messages in the game.
 */
class Logger
{
private:
  int level;
public:
  Logger() { level = 5; };
  virtual ~Logger() {};
  static void setLevel(int);
  static int getLevel(void);
  static void log(int,const char[]);
};

#endif /* LOGGER_H_ */
