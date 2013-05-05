/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * term_utility.h
 *
 * header file for some terminal utilities
 */

#ifndef _TERM_UTILITY_H
#define _TERM_UTILITY_H

#include "register_common.h"
#ifdef WIN_TERM
#include <windows.h>
#endif

class Term {
    public:
        /* default constructor/destructor */
        Term();
        ~Term();

        /*
         * init
         *
         * Init the terminal environment
         */
        void init();

        /*
         * clr
         *
         * Clear the screen
         */
        void clr();

        /*
         * restore
         *
         * Restore the terminal environment
         */
        void restore();

    private:
        #ifdef WIN_TERM
        HANDLE hStdOut;
        #endif
};

#endif
