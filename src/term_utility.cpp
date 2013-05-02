/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * term_utility.cpp
 *
 * Some terminal utilities
 */

#include "term_utility.h"
#ifdef WIN_TERM
#include <conio.h>
#endif

#include <iostream>
using std::cout;
using std::endl;

void term_init() {
    #ifndef WIN_TERM
    cout << "\0337\033[?47h\033[1;1H";
    #endif
    term_clr();
}

void term_clr() {
    #ifdef WIN_TERM
    clrscr();
    #else
    cout << "\033[2J\033[1;1H";
    #endif
}

void term_restore() {
    term_clr();
    #ifndef WIN_TERM
    cout << "\0338\033[?47l";
    #endif
}
