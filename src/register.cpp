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

#include "register_common.h"
#include "term_utility.h"
#include "register_system.h"

int main(int argc, char **argv) {
    Term terminal;
    RegisterSystem sys(&terminal);
    //Execute System
    sys.exec();
    return 0;
}
