/**
 * @file ApplicationModuleExitCode.h
 *
 *  Created on: 15 Feb 2010
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef APPLICATION_MODULE_EXIT_CODE_H_
#define APPLICATION_MODULE_EXIT_CODE_H_

enum ApplicationModuleExitCode {
    NO_EXIT = 0,
    EXIT_APPLICATION = 1,
    EXIT_MODULE_AND_LOAD_MYSTERY_GENERATOR = 2,
    EXIT_MODULE_AND_LOAD_MONSTER_GENERATOR = 3,
    EXIT_MODULE_AND_LOAD_MAIN_MENU = 4};

#endif /* APPLICATION_MODULE_EXIT_CODE_H_ */
