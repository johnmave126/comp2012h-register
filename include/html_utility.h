/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * html_utility.h
 *
 * header file for some html generating utilities
 */

#ifndef _HTML_UTILITY_H
#define _HTML_UTILITY_H

#include "deque.h"
#include <string>
#include <fstream>

using std::ofstream;
using std::string;

//Output file of html
class HTMLFile {
    public:

        /* default constructor/destructor */
        HTMLFile();
        ~HTMLFile();

        /* conversion constructor */
        HTMLFile(string fileName, string title);

        /* copy constructor */
        HTMLFile(HTMLFile&);

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
         * openTag
         *
         * tagName: the tag to open
         * className: the class to append
         *
         * Add a tag to the current file
         */
        void openTag(const char tagName[], const char className[]="");

        /*
         * closeTag
         *
         * Close the current tag
         */
        void closeTag();

        /*
         * writeString
         *
         * content: the content to add
         *
         * Write a series of content to html file
         */
        void writeString(string content);

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
        string file, html_title;

        ofstream os;

        state fstate;

        Deque<string> tag_stack;
};

#endif
