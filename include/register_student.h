/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * register_student.h
 *
 * header file for register student data structure
 */

#ifndef _REGISTER_STUDENT_H
#define _REGISTER_STUDENT_H

#include "register_common.h"
#include <string>
#include <iostream>

using std::string;
using std::ostream;
using std::istream;

class RegisterStudent {
    public:
        /* default constructor/destructor */
        RegisterStudent();
        ~RegisterStudent();

        /* copy constructor */
        RegisterStudent(const RegisterStudent&);

        /* assign operator */
        inline RegisterStudent& operator=(const RegisterStudent&);

        /* compare operators */
        inline bool operator<(const RegisterStudent&) const;
        inline bool operator>=(const RegisterStudent&) const;
        inline bool operator>(const RegisterStudent&) const;
        inline bool operator<=(const RegisterStudent&) const;
        inline bool operator==(const RegisterStudent&) const;
        inline bool operator!=(const RegisterStudent&) const;

        /*
         * getStuId
         *
         * return the student id of the student
         */
        inline string getStuId() const;

        /*
         * setStuId
         *
         * _id: the id to set
         *
         * set the student id of the student
         * no verification will be made
         */
        inline void setStuId(string _id);

        /*
         * getStuName
         *
         * return the name of the student
         */
        inline string getStuName() const;

        /*
         * setStuName
         *
         * _name: the name to set
         *
         * set the name of the student
         * no verification will be made
         */
        inline void setStuName(string _name);

        /*
         * getYear
         *
         * return the year of the student
         */
        inline string getYear() const;

        /*
         * setYear
         *
         * _year: the year to set
         *
         * set the year of the student
         * no verification will be made
         */
        inline void setYear(string _year);

        /*
         * getGender
         *
         * return the gender of the student
         */
        inline string getGender() const;

        /*
         * setGender
         *
         * _gender: the gender to set
         *
         * set the gender of the student
         * no verification will be made
         */
        inline void setGender(string _gender);

        /*
         * serialize
         *
         * os: the output stream
         *
         * output serialization of the student to os
         */
        void serialize(ostream& os) const;

        /*
         * recover
         *
         * is: the input stream
         *
         * recover data from input stream
         * no validation will be made
         */
        void recover(istream& is);
    private:
        //The data
        string id, name, gender, year;
};

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

#endif
