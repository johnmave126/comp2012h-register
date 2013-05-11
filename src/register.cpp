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
#include "register_common.h"
#include "register_menu.h"
#include "regular_expression.h"
#include <iostream>
#include <stdexcept>

using std::cout;
using std::cin;
using std::endl;
using std::runtime_error;


int main(int argc, char **argv) {
    string input;
    RegExp re;
    Term terminal;
    terminal.init();
    getline(cin, input);
    re = input;
    while(true) {
        getline(cin, input);
        if(re.match(input)) {
            cout << "true" << endl;
        }
        else {
            cout << "false" << endl;
        }
    }
    terminal.restore();
    return 0;
}
