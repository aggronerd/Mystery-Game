/*
 * App.h
 *
 *  Created on: 29 Dec 2009
 *      Author: greg
 */

#ifndef APP_H_
#define APP_H_

#include <ClanLib/core.h>
#include "Logger.h"

class Application
{
public:
  Application() {};
  virtual int main(const std::vector<CL_String> &args);
};

#endif /* APP_H_ */
