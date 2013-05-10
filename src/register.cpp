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
#include "hashmap.h"
#include <iostream>
#include <stdexcept>

using std::cout;
using std::cin;
using std::endl;
using std::runtime_error;


int main(int argc, char **argv) {
    int k = 0;
    Term terminal;
    RegisterMenu m(&terminal, NULL, "HKUST Course Registration System");
    terminal.init();
    m.exec();
    terminal.restore();
    return 0;
}
