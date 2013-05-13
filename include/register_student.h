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
    private:
        //The data
        string id, name, gender, year;
};

#endif
