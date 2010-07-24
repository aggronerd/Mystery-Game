/**
 * @file App.h
 *
 *  Created on: 29 Dec 2009
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <ClanLib/core.h>

/**
 * The Application object provides transition between the
 * modules of the overall application. It instantiates a
 * clanLib window and instantiates the other shared parts
 * of the engine.
 */
class Application
{
public:
  Application();
  virtual ~Application();
  virtual int main(const std::vector<CL_String8> &args);
  static void log(const int, const CL_String8&);
private:
  const static int logging_level = 5; //Highest level.
};

#endif /* APPLICATION_H_ */
