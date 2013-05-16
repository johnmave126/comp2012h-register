/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * register_course_selection.cpp
 *
 * register course selection structure
 */

#include "register_common.h"
#include "register_course_selection.h"
#include <string>
#include <cstdio>
#include <iostream>
#include <stdexcept>

using std::string;
using std::ostream;
using std::istream;
using std::runtime_error;

RegisterCourseSelection::RegisterCourseSelection()
:mark("N/A") {
}

RegisterCourseSelection::~RegisterCourseSelection() {
}

RegisterCourseSelection::RegisterCourseSelection(const RegisterCourseSelection& r)
:id(r.id), code(r.code), mark(r.mark) {
}

void RegisterCourseSelection::serialize(ostream& os) const {
    char buff[16];
    int tmp;

    //ID
    tmp = id.length();
    PACK_NUMBER(tmp, buff)
    os.write(buff, 4);
    os.write(id.c_str(), id.size());
    buff[0] = 255;
    os.write(buff, 1);

    //Code
    tmp = code.length();
    PACK_NUMBER(tmp, buff)
    os.write(buff, 4);
    os.write(code.c_str(), code.size());
    buff[0] = 255;
    os.write(buff, 1);

    //Mark
    tmp = mark.length();
    PACK_NUMBER(tmp, buff)
    os.write(buff, 4);
    os.write(mark.c_str(), mark.size());
    buff[0] = 255;
    os.write(buff, 1);

    buff[0] = 0;
    os.write(buff, 1);
}

void RegisterCourseSelection::recover(istream& is) {
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

    //Read length of exam mark
    is.read(buff, 4);
    tmp = UNPACK_NUMBER(buff);
    mark.clear();
    for(i = 0; i < static_cast<int>(tmp); i++) {
        mark.push_back(is.get());
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
