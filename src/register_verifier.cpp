/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * register_verifier.cpp
 *
 * a set of data verifier
 */

#include "register_common.h"
#include "register_verifier.h"
#include "regular_expression.h"
#include <string>
using std::string;

RegisterVerifier::RegisterVerifier()
:v(ELFHash, 23) {
}

RegisterVerifier::~RegisterVerifier() {
}

void RegisterVerifier::insert(string name, string regex) {
    v.insert(name, RegExp(regex));
}

bool RegisterVerifier::verify(string name, string query) {
    RegExp *re = v[name];
    if(re) {
        return re->match(query);
    }
    return false;
}
