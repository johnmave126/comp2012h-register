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
#include <stdexcept>

using std::string;
using std::ostream;
using std::istream;
using std::runtime_error;

RegisterCourse::RegisterCourse() {
}

RegisterCourse::~RegisterCourse() {
}

RegisterCourse::RegisterCourse(const RegisterCourse& r)
:code(r.code), name(r.name), credit(r.credit) {
}

void RegisterCourse::serialize(ostream& os) const {
    char buff[16];
    int tmp;

    //Code
    tmp = code.length();
    PACK_NUMBER(tmp, buff)
    os.write(buff, 4);
    os.write(code.c_str(), code.size());
    buff[0] = 255;
    os.write(buff, 1);

    //Name
    tmp = name.length();
    PACK_NUMBER(tmp, buff)
    os.write(buff, 4);
    os.write(name.c_str(), name.size());
    buff[0] = 255;
    os.write(buff, 1);

    //Credit
    tmp = credit.length();
    PACK_NUMBER(tmp, buff)
    os.write(buff, 4);
    os.write(credit.c_str(), credit.size());
    buff[0] = 255;
    os.write(buff, 1);

    buff[0] = 0;
    os.write(buff, 1);
}

void RegisterCourse::recover(istream& is) {
    char buff[16];
    int i;
    unsigned int tmp;

    //Read length of course code
    is.read(buff, 4);
    tmp = UNPACK_NUMBER(buff);
    code.clear();
    for(i = 0; i < static_cast<int>(tmp); i++) {
        code.push_back(is.get());
    }
    is.read(buff, 1);
    if(buff[0] != -1) {
        throw runtime_error("Corrupted");
    }

    //Read length of course name
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

    //Read length of course credit
    is.read(buff, 4);
    tmp = UNPACK_NUMBER(buff);
    credit.clear();
    for(i = 0; i < static_cast<int>(tmp); i++) {
        credit.push_back(is.get());
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
