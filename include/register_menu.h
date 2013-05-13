/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * register_menu.h
 *
 * header file for a extendable menu
 */

#ifndef _REGISTER_MENU_H
#define _REGISTER_MENU_H

#include "register_common.h"
#include "term_utility.h"
#include <vector>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::vector;

class RegisterMenu: public RegisterObject {
    //Event necessary
    REGISTER_EVENT(RegisterMenu)
    public:
        /* default constructor/destructor */
        RegisterMenu();
        ~RegisterMenu();

        /* copy constructor */
        RegisterMenu(const RegisterMenu&);

        /* conversion constructor */
        explicit RegisterMenu(Term* term, RegisterObject* _parent = NULL, string _title = "Untitled");

        /* assign operator */
        RegisterMenu& operator=(const RegisterMenu&);

        /*
         * setTitle
         *
         * title: the title of the menu
         *
         * set the title of the menu
         */
        void setTitle(string _title);

        /*
         * insertItem
         *
         * title: the title of the item
         * item: the menuitem to insert, another menu
         *
         * append a menu item to this menu
         */
        void insertItem(string _title, RegisterMenu* item);

        /*
         * insertItem
         *
         * title: the title of the item
         * obj: the handler of the item
         * event: the event to trigger
         *
         * append a menu item to this menu, the function
         * works the same as above, except for appending
         * an action instead of another menu
         */
        void insertItem(string _title, RegisterObject* obj, string event);

        /*
         * exec
         *
         * execute the menu
         * return 1 if keep the parent menu, 0 to goto upper level
         */
        int exec();

    private:
        typedef struct {
            string title;
            RegisterObject *item;
            int idx;
        } Item;

        /*
         * displayMenu
         *
         * Display the menu
         */
        void displayMenu() const;

        //The list of item
        vector<Item> subItems;

        //The Terminal handler
        Term* activeTerm;

        //The title of the menu
        string title;
};

#endif
