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

inline RegisterStudent& RegisterStudent::operator=(const RegisterStudent& r) {
    //Simply copy
    id = r.id;
    name = r.name;
    gender = r.gender;
    year = r.year;
    return (*this);
}

inline bool RegisterStudent::operator<(const RegisterStudent& r) const {
    //Use id as primary key
    return id < r.id;
}

inline bool RegisterStudent::operator>=(const RegisterStudent& r) const {
    //Use id as primary key
    return id >= r.id;
}

inline bool RegisterStudent::operator>(const RegisterStudent& r) const {
    //Use id as primary key
    return id > r.id;
}

inline bool RegisterStudent::operator<=(const RegisterStudent& r) const {
    //Use id as primary key
    return id <= r.id;
}

inline bool RegisterStudent::operator==(const RegisterStudent& r) const {
    //Use id as primary key
    return id == r.id;
}

inline bool RegisterStudent::operator!=(const RegisterStudent& r) const {
    //Use id as primary key
    return id != r.id;
}

inline string RegisterStudent::getStuId() const {
    return id;
}

inline void RegisterStudent::setStuId(string _id) {
    id = _id;
}

inline string RegisterStudent::getStuName() const {
    return name;
}

inline void RegisterStudent::setStuName(string _name) {
    name = _name;
}

inline string RegisterStudent::getYear() const {
    return year;
}

inline void RegisterStudent::setYear(string _year) {
    year = _year;
}

inline string RegisterStudent::getGender() const {
    return gender;
}

inline void RegisterStudent::setGender(string _gender) {
    gender = _gender;
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
