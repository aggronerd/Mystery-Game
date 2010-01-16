/*
 * App.h
 *
 *  Created on: 29 Dec 2009
 *      Author: greg
 */

#ifndef APP_H_
#define APP_H_

#include <ClanLib/core.h>

#define LOG_LEVEL_DEBUG 5
#define LOG_LEVEL_INFO 0
#define ENABLE_LOGGING

class Application
{
public:
  Application();
  virtual ~Application();
  virtual int main(const std::vector<CL_String> &args);
  static void log(const int, const CL_String&);
private:
  const static int logging_level = 5; //Highest level.
};

#endif /* APP_H_ */
