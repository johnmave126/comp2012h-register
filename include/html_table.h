/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * html_table.h
 *
 * header file for some table support of HTML
 */

#ifndef _HTML_TABLE_H
#define _HTML_TABLE_H

#include "html_utility.h"
#include "deque.h"
#include <string>

using std::string;

//Output file of html
class HTMLTable {
    public:

        /* default constructor/destructor */
        HTMLTable();
        ~HTMLTable();

        /* conversion constructor */
        HTMLTable(HTMLFile *_file, string _title = "", bool index = true);

        /* copy constructor */
        HTMLTable(HTMLTable&);

        /*
         * insertHead
         *
         * _head: a head to add
         *
         * Add the head to the table
         */
        void insertHead(string _head);

        /*
         * begin
         *
         * Open the file and write header infomation
         * throw std::string if any error occuurs
         */
        void begin();

        /*
         * end
         *
         * End the file and close it
         * throw std::string if any error occuurs
         */
        void end();

        /*
         * beginRow
         *
         * Start a row
         */
        void beginRow();

        /*
         * endRow
         *
         * End the current row
         */
        void endRow();

        /*
         * insertCell
         *
         * content: the content in the cell
         *
         * Add a cell in the table
         */
        void insertCell(string content);

        //Sate of the current file
        enum state {
            ready = 0,
            opened,
            closed
        };

        /*
         * getState
         *
         * Return the state of the htmlfile
         */
        state getState() {return fstate;}

    private:
        HTMLFile *file;
        string title;
        state fstate;
        int idx;

        Deque<string> heads;
};

#endif
