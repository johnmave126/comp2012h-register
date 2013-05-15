/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * register_system.h
 *
 * header file for register system
 */

#ifndef _REGISTER_SYSTEM_H
#define _REGISTER_SYSTEM_H

#include "register_common.h"
#include "term_utility.h"
#include "sortlist.h"
#include "hashmap.h"
#include "register_verifier.h"
#include "register_menu.h"
#include "register_student.h"
#include "register_course.h"
#include "register_course_selection.h"
#include <string>

using std::string;

class RegisterSystem: public RegisterObject {
    //Event necessary
    REGISTER_EVENT(RegisterSystem)
    public:
        /* default constructor/destructor */
        RegisterSystem();
        ~RegisterSystem();

        /* conversion constructor */
        explicit RegisterSystem(Term* _terminal);

        //Begin Student Management

        /*
         * insertStudent
         *
         * handle when insert student
         */
        int insertStudent();

        /*
         * modifyStudent
         *
         * handle when modify student
         */
        int modifyStudent();

        /*
         * deleteStudent
         *
         * handle when delete student
         */
        int deleteStudent();

        /*
         * queryStudent
         *
         * handle when query student
         */
        int queryStudent();

        //End Student Management

        //Begin Course Management

        /*
         * insertCourse
         *
         * handle when insert course
         */
        int insertCourse();

        /*
         * modifyCourse
         *
         * handle when modify course
         */
        int modifyCourse();

        /*
         * deleteCourse
         *
         * handle when delete course
         */
        int deleteCourse();

        /*
         * queryCourse
         *
         * handle when query course
         */
        int queryCourse();

        //End Course Management

        //Begin Course Registration

        /*
         * addCourse
         *
         * handle when add course
         */
        int addCourse();

        /*
         * dropCourse
         *
         * handle when drop course
         */
        int dropCourse();

        /*
         * modifyExamMark
         *
         * handle when modify exam mark
         */
        int modifyExamMark();

        /*
         * queryRegistration
         *
         * handle when query registration
         */
        int queryRegistration();

        //End Course Registration

        /*
         * exec
         *
         * Execute the system
         */
        void exec();

    private:
        /*
         * init_verifier
         *
         * Init the verifier
         */
        void init_verifier();

        /*
         * init_menu
         *
         * Init the menu
         */
        void init_menu();

        //The terminal support
        Term* terminal;

        //The main menu
        RegisterMenu menu;

        //The verifier
        RegisterVerifier verifier;

        //The hashmap for students
        Hashmap<string, RegisterStudent, int(*)(const string&, int)> DataStudents;

        //The hashmap for courses
        Hashmap<string, RegisterCourse, int(*)(const string&, int)> DataCourses;

        //The list of course selection
        SortList<RegisterCourseSelection> DataCourseSelections;

        //The extra indices
        typedef Hashmap<string, RegisterCourseSelection*, int(*)(const string&, int), bool(*)(RegisterCourseSelection* const &, RegisterCourseSelection* const &)> spHasp;
        spHasp CourseSelectionID;
        spHasp CourseSelectionCode;

        //Helper classes to delete things
        class delStuId {
            public:
                delStuId(string _id):id(_id) {}
                bool operator()(const RegisterCourseSelection* r) {
                    return r->getStuId() == id;
                }
                bool operator()(const RegisterCourseSelection& r) {
                    return r.getStuId() == id;
                }
            private:
                string id;
        };
        class delCode {
            public:
                delCode(string _code):code(_code) {}
                bool operator()(const RegisterCourseSelection* r) {
                    return r->getCode() == code;
                }
                bool operator()(const RegisterCourseSelection& r) {
                    return r.getCode() == code;
                }
            private:
                string code;
        };
        class delIdCode {
            public:
                delIdCode(string _id, string _code):id(_id), code(_code) {}
                bool operator()(const RegisterCourseSelection* r) {
                    return r->getStuId() == id && r->getCode() == code;
                }
                bool operator()(const RegisterCourseSelection& r) {
                    return r.getStuId() == id && r.getCode() == code;
                }
            private:
                string id, code;
        };
        class delCourseSelection {
            public:
                delCourseSelection(RegisterSystem *_sys): sys(_sys) {}
                void operator()(RegisterCourseSelection* r) {
                    delStuId t(r->getStuId());
                    sys->CourseSelectionCode.remove(r->getCode(), t);
                }
            private:
                RegisterSystem *sys;
        };
};

#endif
