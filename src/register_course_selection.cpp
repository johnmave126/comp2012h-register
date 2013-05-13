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

using std::string;
using std::ostream;

RegisterCourseSelection::RegisterCourseSelection() {
}

RegisterCourseSelection::~RegisterCourseSelection() {
}

RegisterCourseSelection::RegisterCourseSelection(const RegisterCourseSelection& r)
:id(r.id), code(r.code), mark(r.mark) {
}

inline RegisterCourseSelection& RegisterCourseSelection::operator=(const RegisterCourseSelection& r) {
    //Simply copy
    id = r.id;
    code = r.code;
    mark = r.mark;
    return (*this);
}

inline bool RegisterCourseSelection::operator<(const RegisterCourseSelection& r) const {
    //Use id as primary key, code as secondary key
    return (id == r.id)?(code < r.code):(id < r.id);
}

inline bool RegisterCourseSelection::operator>=(const RegisterCourseSelection& r) const {
    //Reuse
    return !((*this) < r);
}

inline bool RegisterCourseSelection::operator>(const RegisterCourseSelection& r) const {
    //Use id as primary key, code as secondary key
    return (id == r.id)?(code > r.code):(id > r.id);
}

inline bool RegisterCourseSelection::operator<=(const RegisterCourseSelection& r) const {
    //Reuse
    return !((*this) > r);
}

inline bool RegisterCourseSelection::operator==(const RegisterCourseSelection& r) const {
    //Use id as primary key, code as secondary key
    return id == r.id && code == r.code;
}

inline bool RegisterCourseSelection::operator!=(const RegisterCourseSelection& r) const {
    //Use id as primary key, code as secondary key
    return id != r.id || code != r.code;
}

inline string RegisterCourseSelection::getStuId() const {
    return id;
}

inline void RegisterCourseSelection::setStuId(string _id) {
    id = _id;
}

inline string RegisterCourseSelection::getCode() const {
    return code;
}

inline void RegisterCourseSelection::setCode(string _code) {
    code = _code;
}

inline string RegisterCourseSelection::getMark() const {
    return mark;
}

inline void RegisterCourseSelection::setMark(string _mark) {
    mark = _mark;
}

void RegisterCourseSelection::serialize(ostream& os) const {
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

    //Mark
    tmp = mark.length();
    buff[0] = static_cast<char>(tmp >> 24);
    buff[1] = static_cast<char>((tmp >> 16) & 0xFF);
    buff[2] = static_cast<char>((tmp >> 8) & 0xFF);
    buff[3] = static_cast<char>(tmp & 0xFF);
    os.write(buff, 4);
    os.write(mark.c_str(), mark.size());
    buff[0] = 255;
    os.write(buff, 1);

    buff[0] = 0;
    os.write(buff, 1);
}
