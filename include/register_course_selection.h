/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * register_course_selection.h
 *
 * header file for register course data structure
 */

#ifndef _REGISTER_COURSE_SELECTION_H
#define _REGISTER_COURSE_SELECTION_H

#include "register_common.h"
#include <string>
#include <iostream>

using std::string;
using std::ostream;

class RegisterCourseSelection {
    public:
        /* default constructor/destructor */
        RegisterCourseSelection();
        ~RegisterCourseSelection();

        /* copy constructor */
        RegisterCourseSelection(const RegisterCourseSelection&);

        /* assign operator */
        RegisterCourseSelection& operator=(const RegisterCourseSelection&);

        /* compare operators */
        bool operator<(const RegisterCourseSelection&) const;
        bool operator>=(const RegisterCourseSelection&) const;
        bool operator>(const RegisterCourseSelection&) const;
        bool operator<=(const RegisterCourseSelection&) const;
        bool operator==(const RegisterCourseSelection&) const;
        bool operator!=(const RegisterCourseSelection&) const;

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
         * getMark
         *
         * return the exam mark of the course
         */
        inline string getMark() const;

        /*
         * setMark
         *
         * _mark: the mark to set
         *
         * set the mark of the course
         * no verification will be made
         */
        inline void setMark(string _mark);

        /*
         * serialize
         *
         * os: the output stream
         *
         * output serialization of the course selection to os
         */
        void serialize(ostream& os) const;
    private:
        //The data
        string id, code, mark;
};

#endif
