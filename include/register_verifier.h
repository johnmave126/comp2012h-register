/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * register_verifier.h
 *
 * header file for a data verifier
 */

#ifndef _REGISTER_VERIFIER_H
#define _REGISTER_VERIFIER_H

#include "register_common.h"
#include "regular_expression.h"
#include "hashmap.h"

class RegisterVerifier {
    public:
        /* default constructor/destructor */
        RegisterVerifier();
        ~RegisterVerifier();

        /*
         * insert
         *
         * name: the name of the rule
         * regex: the regular expression
         *
         * Add a verifier
         */
        void insert(string name, string regex);

        /*
         * verify
         *
         * name: the name of the rule
         * query: the string to verify
         *
         * Verify a string
         * return true if success, false otherwise
         */
        bool verify(string name, string query);

    private:

        //Store verifiers
        Hashmap<string, RegExp, int(*)(const string&, int)> v;
};

#endif
