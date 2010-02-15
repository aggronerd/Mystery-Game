// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*
    This is a rather involved example illustrating the use of the GUI api from 
    the dlib C++ Library.   This program is a fully functional utility for
    creating Bayesian Networks.  It allows the user to graphically draw the network,
    save/load the network to/from disk, and also to calculate the posterior 
    probability of any node in the network given a set of evidence.

    This is not the first dlib example program you should be looking at.  If you
    want to see a simpler GUI example please look at the gui_api_ex.cpp or
    image_ex.cpp example.  

    If you want to understand how to use the Bayesian Network utilities in the library
    you should definitely look at the bayes_net_ex.cpp example program.  It gives a
    comprehensive introduction to creating and manipulating Bayesian Networks.  If you
    want to see how to load a saved network from disk and use it in a non-GUI application
    then look at the bayes_net_from_disk_ex.cpp example.


    Now all of that being said, if you have already looked at the other relevant 
    examples and want to see a more in-depth example then by all means, continue reading. :)
*/

#include "MainWindow.h"

int main()
{
    // create our window
    MainWindow my_window;

    // tell our window to put itself on the screen
    my_window.show();

    // wait until the user closes this window before we let the program terminate.
    my_window.wait_until_closed();
}

#ifdef WIN32
//  If you use main() as your entry point when building a program on MS Windows then
//  there will be a black console window associated with your application.  If you
//  want your application to not have this console window then you need to build
//  using the WinMain() entry point as shown below and also set your compiler to 
//  produce a "Windows" project instead of a "Console" project.  In visual studio
//  this can be accomplished by going to project->properties->general configuration->
//  Linker->System->SubSystem and selecting Windows instead of Console.  
// 
int WINAPI WinMain (HINSTANCE, HINSTANCE, PSTR cmds, int)
{
    main();
    return 0;
}
#endif

