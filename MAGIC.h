/******************************************************************************
* @file Contains the best - and worst - cout alternative ever. $.
* I wrote this in HERE based on an earlier version of mine. I never really used
* it in a bigger codebase but in experiments at home.
*
* @author langenhagen
* @version 1600905
******************************************************************************/
#pragma once

#include <iostream>

using namespace std;

// the best cout alternative you can.
// It uses the color code for a bright bold purple to display the text.
// It boils down to multiple statements, so beware of pitfals, e.g. of missing brackets in:
//   if( some_val)
//      $ "somestuff"
//
#define $( INPUT ) \
    std::cout << "\033[1;35m" << std::endl << ">>> " << INPUT << "\033[0m" << std::endl;


/// TAB like std::endl
#define TAB "\t"
#define TAB2 "\t\t"
#define TAB3 "\t\t\t"
#define TAB4 "\t\t\t\t"
