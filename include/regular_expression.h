/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * regular_expression.h
 *
 * header file for a simple regular expression engine
 */

#ifndef _REGULAR_EXPRESSION_H
#define _REGULAR_EXPRESSION_H

#include "register_common.h"
#include <string>
#include <vector>
#include <cstring>
#include <cctype>

using std::string;
using std::vector;

//The engine
/*Some specification
 *meta characters
 *character     meaning
 *c             literally character
 *^             beginning of a string
 *$             end of a string
 *.             any character
 *\d            number 0-9
 *\s            white characters
 *\w            alphanumeric characters a-zA-Z
 *\c            non-capital alphanumeric characters a-z
 *\C            capitalized alphanumeric characters A-Z
 *\...          espaced characters
 *(...)         a group of expression
 *[...]         a set of character
 *
 *quantifiers
 *characters    meaning
 **             match zero or more occurence
 *{int}         match exactly int occurences
 *{min,max}     match at least min, and at most max occurmences
 */
class RegExp {
    public:
        /* default constructor/destructor */
        RegExp();
        ~RegExp();

        /* conversion constructor */
        RegExp(string _r);

        /* copy constructor */
        RegExp(const RegExp&);

        /* assign operator */
        RegExp& operator=(const RegExp&);

        //Only for compatibility
        /* compare operators */
        bool operator<(const RegExp& r) {return Re < r.Re;}
        bool operator<=(const RegExp& r) {return Re <= r.Re;}
        bool operator>(const RegExp& r) {return Re > r.Re;}
        bool operator>=(const RegExp& r) {return Re >= r.Re;}
        bool operator==(const RegExp& r) {return Re == r.Re;}
        bool operator!=(const RegExp& r) {return Re != r.Re;}

        /*
         * match
         *
         * str: the string to match
         *
         * Match the regular expression with string
         * true for success, false for fail
         */
        bool match(string& str);

        /*
         * match
         *
         * str: the string to match
         *
         * Match the regular expression with string
         * true for success, false for fail
         */
        bool match(const char *str);

    protected:
        /*
         * matchhere
         *
         * regex: start of regular expression
         * str: the string to match
         *
         * Match the regular expression here with string
         * true for success, false for fail
         */
        static bool matchhere(const char *regex, const char *str);

        /*
         * matchstar
         *
         * regex: start of regular expression
         * c: the char before *
         * str: the string to match
         *
         * Match the regular expression c*
         * true for success, false for fail
         */
        static bool matchstar(const char *regex, char c, const char *str);

        /*
         * matchstar
         *
         * regex: start of regular expression
         * c: the special characters
         * str: the string to match
         *
         * Match the regular expression [c]*
         * true for success, false for fail
         */
        static bool matchstar(const char *regex, string c, const char *str);

        /*
         * matchstar_s
         *
         * regex: start of regular expression
         * c: the special char before *
         * str: the string to match
         *
         * Match the regular expression \c*
         * true for success, false for fail
         */
        static bool matchstar_s(const char *regex, char c, const char *str);

        /*
         * matchexactly
         *
         * regex: start of regular expression
         * c: the character
         * time: the occurence of the c
         * str: the string to match
         *
         * Match the regular expression c{time}
         * true for success, false for fail
         */
        static bool matchexactly(const char *regex, char c, int time, const char *str);

        /*
         * matchexactly
         *
         * regex: start of regular expression
         * c: the special characters
         * time: the occurence of the c
         * str: the string to match
         *
         * Match the regular expression [c]{time}
         * true for success, false for fail
         */
        static bool matchexactly(const char *regex, string c, int time, const char *str);

        /*
         * matchexactly_s
         *
         * regex: start of regular expression
         * c: the special char before *
         * time: the occurence of the c
         * str: the string to match
         *
         * Match the regular expression \c{time}
         * true for success, false for fail
         */
        static bool matchexactly_s(const char *regex, char c, int time, const char *str);

        /*
         * matchminmax
         *
         * regex: start of regular expression
         * c: the character
         * min: the minimum occurence of the c
         * max: the maximum occurence of the c
         * str: the string to match
         *
         * Match the regular expression c{min,max}
         * true for success, false for fail
         */
        static bool matchminmax(const char *regex, char c, int min, int max, const char *str);

        /*
         * matchminmax
         *
         * regex: start of regular expression
         * c: the special characters
         * min: the minimum occurence of the c
         * max: the maximum occurence of the c
         * str: the string to match
         *
         * Match the regular expression [c]{min,max}
         * true for success, false for fail
         */
        static bool matchminmax(const char *regex, string c, int min, int max, const char *str);

        /*
         * matchminmax_s
         *
         * regex: start of regular expression
         * c: the special char before *
         * min: the minimum occurence of the c
         * max: the maximum occurence of the c
         * str: the string to match
         *
         * Match the regular expression \c{min,max}
         * true for success, false for fail
         */
        static bool matchminmax_s(const char *regex, char c, int min, int max, const char *str);

        /*
         * testcharacter
         *
         * s: the special character
         * c: the tested char
         *
         * test if c is \s
         * true for success, false for fail
         */
        static bool testcharacter(char s, char c);

        /*
         * testcharacter
         *
         * s: the special characters
         * c: the tested char
         *
         * test if c is [s]
         * true for success, false for fail
         */
        static bool testcharacter(string s, char c);

        //The regular expression stored
        string Re;
};

#endif
