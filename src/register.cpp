/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * register.cpp
 *
 * main entry of the program
 */

#include "term_utility.h"
#include <iostream>

using std::cout;
using std::cin;

int main(int argc, char **argv) {
    int k = 0;
    term_init();
    while(k != 1) {
        cout << "Input 1 to quit:\n";
        cin >> k;
        term_clr();
    }
    term_restore();
    return 0;
}
