/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * register_course.cpp
 *
 * register course data structure
 */

#include "register_common.h"
#include "register_course.h"
#include <string>
#include <cstdio>
#include <iostream>

using std::string;
using std::ostream;

RegisterCourse::RegisterCourse() {
}

RegisterCourse::~RegisterCourse() {
}

RegisterCourse::RegisterCourse(const RegisterCourse& r)
:code(r.code), name(r.name), credit(r.credit) {
}

inline RegisterCourse& RegisterCourse::operator=(const RegisterCourse& r) {
    //Simply copy
    code = r.code;
    name = r.name;
    credit = r.credit;
    return (*this);
}

inline bool RegisterCourse::operator<(const RegisterCourse& r) const {
    //Use code as primary key
    return code < r.code;
}

inline bool RegisterCourse::operator>=(const RegisterCourse& r) const {
    //Use code as primary key
    return code >= r.code;
}

inline bool RegisterCourse::operator>(const RegisterCourse& r) const {
    //Use code as primary key
    return code > r.code;
}

inline bool RegisterCourse::operator<=(const RegisterCourse& r) const {
    //Use code as primary key
    return code <= r.code;
}

inline bool RegisterCourse::operator==(const RegisterCourse& r) const {
    //Use code as primary key
    return code == r.code;
}

inline bool RegisterCourse::operator!=(const RegisterCourse& r) const {
    //Use code as primary key
    return code != r.code;
}

inline string RegisterCourse::getCode() const {
    return code;
}

inline void RegisterCourse::setCode(string _code) {
    code = _code;
}

inline string RegisterCourse::getCourseName() const {
    return name;
}

inline void RegisterCourse::setCourseName(string _name) {
    name = _name;
}

inline string RegisterCourse::getCredit() const {
    return credit;
}

inline void RegisterCourse::setCredit(string _credit) {
    credit = _credit;
}

void RegisterCourse::serialize(ostream& os) const {
    char buff[16];
    int tmp;

    //Code
    tmp = code.length();
    buff[0] = static_cast<char>(tmp >> 24);
    buff[1] = static_cast<char>((tmp >> 16) & 0xFF);
    buff[2] = static_cast<char>((tmp >> 8) & 0xFF);
    buff[3] = static_cast<char>(tmp & 0xFF);
    os.write(buff, 4);
    os.write(code.c_str(), code.size());
    buff[0] = 255;
    os.write(buff, 1);

    //Name
    tmp = name.length();
    buff[0] = static_cast<char>(tmp >> 24);
    buff[1] = static_cast<char>((tmp >> 16) & 0xFF);
    buff[2] = static_cast<char>((tmp >> 8) & 0xFF);
    buff[3] = static_cast<char>(tmp & 0xFF);
    os.write(buff, 4);
    os.write(name.c_str(), name.size());
    buff[0] = 255;
    os.write(buff, 1);

    //Credit
    tmp = credit.length();
    buff[0] = static_cast<char>(tmp >> 24);
    buff[1] = static_cast<char>((tmp >> 16) & 0xFF);
    buff[2] = static_cast<char>((tmp >> 8) & 0xFF);
    buff[3] = static_cast<char>(tmp & 0xFF);
    os.write(buff, 4);
    os.write(credit.c_str(), credit.size());
    buff[0] = 255;
    os.write(buff, 1);

    buff[0] = 0;
    os.write(buff, 1);
}
