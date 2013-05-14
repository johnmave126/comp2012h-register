/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * register_student.cpp
 *
 * register student data structure
 */

#include "register_common.h"
#include "register_student.h"
#include <string>
#include <cstdio>
#include <iostream>

using std::string;
using std::ostream;

RegisterStudent::RegisterStudent() {
}

RegisterStudent::~RegisterStudent() {
}

RegisterStudent::RegisterStudent(const RegisterStudent& r)
:id(r.id), name(r.name), gender(r.gender), year(r.year) {
}

void RegisterStudent::serialize(ostream& os) const {
    char buff[16];
    int tmp;

    //ID
    tmp = id.length();
    buff[0] = static_cast<char>(tmp >> 24);
    buff[1] = static_cast<char>((tmp >> 16) & 0xFF);
    buff[2] = static_cast<char>((tmp >> 8) & 0xFF);
    buff[3] = static_cast<char>(tmp & 0xFF);
    os.write(buff, 4);
    os.write(id.c_str(), id.size());
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

    //Gender
    tmp = gender.length();
    buff[0] = static_cast<char>(tmp >> 24);
    buff[1] = static_cast<char>((tmp >> 16) & 0xFF);
    buff[2] = static_cast<char>((tmp >> 8) & 0xFF);
    buff[3] = static_cast<char>(tmp & 0xFF);
    os.write(buff, 4);
    os.write(gender.c_str(), gender.size());
    buff[0] = 255;
    os.write(buff, 1);

    //Year
    tmp = year.length();
    buff[0] = static_cast<char>(tmp >> 24);
    buff[1] = static_cast<char>((tmp >> 16) & 0xFF);
    buff[2] = static_cast<char>((tmp >> 8) & 0xFF);
    buff[3] = static_cast<char>(tmp & 0xFF);
    os.write(buff, 4);
    os.write(year.c_str(), year.size());
    buff[0] = 255;
    os.write(buff, 1);

    buff[0] = 0;
    os.write(buff, 1);
}
