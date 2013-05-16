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
#include <stdexcept>

using std::string;
using std::ostream;
using std::istream;
using std::runtime_error;

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
    PACK_NUMBER(tmp, buff)
    os.write(buff, 4);
    os.write(id.c_str(), id.size());
    buff[0] = 255;
    os.write(buff, 1);

    //Name
    tmp = name.length();
    PACK_NUMBER(tmp, buff)
    os.write(buff, 4);
    os.write(name.c_str(), name.size());
    buff[0] = 255;
    os.write(buff, 1);

    //Gender
    tmp = gender.length();
    PACK_NUMBER(tmp, buff)
    os.write(buff, 4);
    os.write(gender.c_str(), gender.size());
    buff[0] = 255;
    os.write(buff, 1);

    //Year
    tmp = year.length();
    PACK_NUMBER(tmp, buff)
    os.write(buff, 4);
    os.write(year.c_str(), year.size());
    buff[0] = 255;
    os.write(buff, 1);

    buff[0] = 0;
    os.write(buff, 1);
}

void RegisterStudent::recover(istream& is) {
    char buff[16];
    int i;
    unsigned int tmp;

    //Read length of student id
    is.read(buff, 4);
    tmp = UNPACK_NUMBER(buff);
    id.clear();
    for(i = 0; i < static_cast<int>(tmp); i++) {
        id.push_back(is.get());
    }
    is.read(buff, 1);
    if(buff[0] != -1) {
        throw runtime_error("Corrupted");
    }

    //Read length of student name
    is.read(buff, 4);
    tmp = UNPACK_NUMBER(buff);
    name.clear();
    for(i = 0; i < static_cast<int>(tmp); i++) {
        name.push_back(is.get());
    }
    is.read(buff, 1);
    if(buff[0] != -1) {
        throw runtime_error("Corrupted");
    }

    //Read length of student gender
    is.read(buff, 4);
    tmp = UNPACK_NUMBER(buff);
    gender.clear();
    for(i = 0; i < static_cast<int>(tmp); i++) {
        gender.push_back(is.get());
    }
    is.read(buff, 1);
    if(buff[0] != -1) {
        throw runtime_error("Corrupted");
    }

    //Read length of student year
    is.read(buff, 4);
    tmp = UNPACK_NUMBER(buff);
    year.clear();
    for(i = 0; i < static_cast<int>(tmp); i++) {
        year.push_back(is.get());
    }
    is.read(buff, 1);
    if(buff[0] != -1) {
        throw runtime_error("Corrupted");
    }

    is.read(buff, 1);
    if(buff[0] != 0) {
        throw runtime_error("Corrupted");
    }
}
