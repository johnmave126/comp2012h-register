/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu Code: 20090398
 * 2013 Spring
 *
 * register_course_management.cpp
 *
 * The course management part of RegisterSystem
 */

#include "register_common.h"
#include "register_system.h"
#include "register_verifier.h"
#include "hashmap.h"

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int RegisterSystem::insertCourse() {
    string input;
    RegisterCourse course;
    do {
        //Get course id
        cout << "Enter the course code: ";
        getline(cin, input);
        while(!verifier.verify("Code", input)) {
            cout << "Invalid input, re-enter again [course code]: ";
            getline(cin, input);
        }
        //Check existence
        if(DataCourses[input]) {
            cout << "Course already exist" << endl;
            break;
        }
        course.setCode(input);

        //Get course name
        cout << "Enter the course name: ";
        getline(cin, input);
        while(!verifier.verify("CourseName", input)) {
            cout << "Invalid input, re-enter again [course name]: ";
            getline(cin, input);
        }
        course.setCourseName(input);

        //Get course credit
        cout << "Enter the course credit [0-5]: ";
        getline(cin, input);
        while(!verifier.verify("Credit", input)) {
            cout << "Invalid input, re-enter again [course credit]: ";
            getline(cin, input);
        }
        course.setCredit(input);

        //Insert the course
        DataCourses.insert(course.getCode(), course);

        //Output success message
        cout << "Creation of course record successful" << endl;
    }while(false);

    terminal->pause();
    return 0;
}

int RegisterSystem::modifyCourse() {
    string input;
    RegisterCourse *course;
    do {
        //Get course id
        cout << "Enter the course code: ";
        getline(cin, input);
        while(!verifier.verify("Code", input)) {
            cout << "Invalid input, re-enter again [course code]: ";
            getline(cin, input);
        }
        //Check existence
        course = DataCourses[input];
        if(!course) {
            cout << "Course not exist" << endl;
            break;
        }

        //Get course name
        cout << "Enter the course name [" << course->getCourseName() << "]: ";
        getline(cin, input);
        while(!verifier.verify("CourseName", input)) {
            cout << "Invalid input, re-enter again [course name]: ";
            getline(cin, input);
        }
        course->setCourseName(input);

        //Get course credit
        cout << "Enter the course credit [" << course->getCredit() << "]: ";
        getline(cin, input);
        while(!verifier.verify("Credit", input)) {
            cout << "Invalid input, re-enter again [course credit]: ";
            getline(cin, input);
        }
        course->setCredit(input);

        //Output success message
        cout << "Modification of course record successful" << endl;
    }while(false);

    terminal->pause();
    return 0;
}

int RegisterSystem::deleteCourse() {
    string input;
    RegisterCourse* course;
    RegisterCourseSelection** regInfo;
    do {
        //Get course id
        cout << "Enter the course code: ";
        getline(cin, input);
        while(!verifier.verify("Code", input)) {
            cout << "Invalid input, re-enter again [course code]: ";
            getline(cin, input);
        }
        //Check existence
        course = DataCourses[input];
        if(!course) {
            cout << "Course not exist" << endl;
            break;
        }

        //Check register
        regInfo = CourseSelectionCode[input];
        if(regInfo) {
            cout << "Some students already registered in this course, deletion fail" << endl;
            break;
        }

        //Delete in Course Database
        DataCourses.remove(input);

        //Output success message
        cout << "Deletion of course record successful" << endl;
    }while(false);
    
    terminal->pause();
    return 0;
}

int RegisterSystem::queryCourse() {
    string input;
    RegisterCourse *course;
    do {
        //Get course id
        cout << "Enter the course code: ";
        getline(cin, input);
        while(!verifier.verify("Code", input)) {
            cout << "Invalid input, re-enter again [course code]: ";
            getline(cin, input);
        }
        //Check existence
        course = DataCourses[input];
        if(!course) {
            cout << "Course not exist" << endl;
            break;
        }

        //Put information
        cout << endl;
        cout << "Code:     " << course->getCode() << endl;
        cout << "Name:   " << course->getCourseName() << endl;
        cout << "Credit:   " << course->getCredit() << endl;       
    }while(false);
    
    terminal->pause();
    return 0;
}
