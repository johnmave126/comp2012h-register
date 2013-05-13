/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * register_course.h
 *
 * header file for register course data structure
 */

#ifndef _REGISTER_COURSE_H
#define _REGISTER_COURSE_H

#include "register_common.h"
#include <string>
#include <iostream>

using std::string;
using std::ostream;

class RegisterCourse {
    public:
        /* default constructor/destructor */
        RegisterCourse();
        ~RegisterCourse();

        /* copy constructor */
        RegisterCourse(const RegisterCourse&);

        /* assign operator */
        RegisterCourse& operator=(const RegisterCourse&);

        /* compare operators */
        bool operator<(const RegisterCourse&) const;
        bool operator>=(const RegisterCourse&) const;
        bool operator>(const RegisterCourse&) const;
        bool operator<=(const RegisterCourse&) const;
        bool operator==(const RegisterCourse&) const;
        bool operator!=(const RegisterCourse&) const;

        /*
         * getCode
         *
         * return the course code of the course
         */
        inline string getCode() const;

        /*
         * setCode
         *
         * _code: the code to set
         *
         * set the course code of the course
         * no verification will be made
         */
        inline void setCode(string _code);

        /*
         * getCourseName
         *
         * return the name of the course
         */
        inline string getCourseName() const;

        /*
         * setCourseName
         *
         * _name: the name to set
         *
         * set the name of the course
         * no verification will be made
         */
        inline void setCourseName(string _name);

        /*
         * getCredit
         *
         * return the credit of the course
         */
        inline string getCredit() const;

        /*
         * setCredit
         *
         * _credit: the credit to set
         *
         * set the credit of the course
         * no verification will be made
         */
        inline void setCredit(string _credit);

        /*
         * serialize
         *
         * os: the output stream
         *
         * output serialization of the course to os
         */
        void serialize(ostream& os) const;
    private:
        //The data
        string code, name, credit;
};

#endif
