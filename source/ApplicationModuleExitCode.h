/**
 * @file ApplicationModuleExitCode.h
 *
 *  Created on: 15 Feb 2010
 *      @author Gregory Doran <www.gregorydoran.co.uk>
 */

#ifndef APPLICATION_MODULE_EXIT_CODE_H_
#define APPLICATION_MODULE_EXIT_CODE_H_

enum ApplicationModuleExitCode {
    no_exit = 0,
    exit_application = 1,
    exit_module_and_load_game = 2,
    exit_module_and_load_editor = 3,
    exit_module_and_load_main_menu = 4};

#endif /* APPLICATION_MODULE_EXIT_CODE_H_ */
