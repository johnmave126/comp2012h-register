/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * register_course_registration.cpp
 *
 * The course registration part of RegisterSystem
 */

#include "register_common.h"
#include "register_system.h"
#include "register_verifier.h"
#include "hashmap.h"

#include <iostream>
#include <string>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::runtime_error;

int RegisterSystem::addCourse() {
    string input;
    RegisterStudent *student;
    RegisterCourse *course;
    RegisterCourseSelection regCourse;
    RegisterCourseSelection *refSelection;
    spHasp::Iterator itr;
    bool flag;
    do {
        //Get student id
        cout << "Enter the student ID: ";
        getline(cin, input);
        while(!verifier.verify("ID", input)) {
            cout << "Invalid input, re-enter again [student ID]: ";
            getline(cin, input);
        }
        //Check existence
        student = DataStudents[input];
        if(!student) {
            cout << "Student not exist" << endl;
            break;
        }
        regCourse.setStuId(input);

        //Get Course Code
        cout << "Enter the course Code: ";
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
        regCourse.setCode(input);

        itr = CourseSelectionID.query(regCourse.getStuId());
        flag = false;
        try {
            while(true) {
                if((*itr)->getCode() == input) {
                    flag = true;
                    break;
                }
                itr++;
            }
        }
        catch(runtime_error& e) {
            //Ignore
        }
        if(flag) {
            //Already registered
            cout << "The student already registered the course" << endl;
            break;
        }

        //Insert into SortList
        refSelection = DataCourseSelections.insert(regCourse);

        //Insert into indices
        CourseSelectionID.insert(regCourse.getStuId(), refSelection);
        CourseSelectionCode.insert(input, refSelection);
        
        //Output success message
        cout << "Add course successful" << endl;
    }while(false);

    terminal->pause();
    return 0;
}

int RegisterSystem::dropCourse() {
    string input;
    RegisterStudent *student;
    RegisterCourse *course;
    spHasp::Iterator itr;
    bool flag;
    do {
        //Get student id
        cout << "Enter the student ID: ";
        getline(cin, input);
        while(!verifier.verify("ID", input)) {
            cout << "Invalid input, re-enter again [student ID]: ";
            getline(cin, input);
        }
        //Check existence
        student = DataStudents[input];
        if(!student) {
            cout << "Student not exist" << endl;
            break;
        }

        //Get Course Code
        cout << "Enter the course Code: ";
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

        itr = CourseSelectionID.query(student->getStuId());
        flag = true;
        try {
            while(true) {
                if((*itr)->getCode() == input) {
                    flag = false;
                    break;
                }
                itr++;
            }
        }
        catch(runtime_error& e) {
            //Ignore
        }
        if(flag) {
            //Not recognized
            cout << "The registration record not exist" << endl;
            break;
        }
        
        //Delete in Course Code index
        delStuId tmpDelSI(student->getStuId());
        CourseSelectionCode.remove(input, tmpDelSI);

        //Delete in Course ID index
        delCode tmpDelCC(input);
        CourseSelectionID.remove(student->getStuId(), tmpDelCC);

        //Delete in Course SortList
        delIdCode tmpDelIC(student->getStuId(), input);
        DataCourseSelections.remove(tmpDelIC);

        
        //Output success message
        cout << "Drop course successful" << endl;
    }while(false);

    terminal->pause();
    return 0;
}

int RegisterSystem::modifyExamMark() {
    string input;
    RegisterStudent *student;
    RegisterCourse *course;
    spHasp::Iterator itr;
    bool flag;
    do {
        //Get student id
        cout << "Enter the student ID: ";
        getline(cin, input);
        while(!verifier.verify("ID", input)) {
            cout << "Invalid input, re-enter again [student ID]: ";
            getline(cin, input);
        }
        //Check existence
        student = DataStudents[input];
        if(!student) {
            cout << "Student not exist" << endl;
            break;
        }

        //Get Course Code
        cout << "Enter the course Code: ";
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

        itr = CourseSelectionID.query(student->getStuId());
        flag = true;
        try {
            while(true) {
                if((*itr)->getCode() == input) {
                    flag = false;
                    break;
                }
                itr++;
            }
        }
        catch(runtime_error& e) {
            //Ignore
        }
        if(flag) {
            //Not recognized
            cout << "The registration record not exist" << endl;
            break;
        }
        //Ask for modification
        cout << "Enter the exam mark [" << (*itr)->getMark() << "]: ";
        getline(cin, input);
        while(!verifier.verify("Mark", input)) {
            cout << "Invalid input, re-enter again [exam mark]: ";
            getline(cin, input);
        }
        //Set mark
        (*itr)->setMark(input);

        //Output success message
        cout << "Modification of exam mark successful" << endl;
    }while(false);
    
    terminal->pause();
    return 0;
}

int RegisterSystem::queryRegistration() {
    string input;
    RegisterStudent *student;
    RegisterCourse *course;
    spHasp::Iterator itr;
    bool flag;
    do {
        //Get student id
        cout << "Enter the student ID: ";
        getline(cin, input);
        while(!verifier.verify("ID", input)) {
            cout << "Invalid input, re-enter again [student ID]: ";
            getline(cin, input);
        }
        //Check existence
        student = DataStudents[input];
        if(!student) {
            cout << "Student not exist" << endl;
            break;
        }

        //Get Course Code
        cout << "Enter the course Code: ";
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

        itr = CourseSelectionID.query(student->getStuId());
        flag = true;
        try {
            while(true) {
                if((*itr)->getCode() == input) {
                    flag = false;
                    break;
                }
                itr++;
            }
        }
        catch(runtime_error& e) {
            //Ignore
        }
        if(flag) {
            //Not recognized
            cout << "The registration record not exist" << endl;
            break;
        }

        //Put information
        cout << endl;
        cout << "Student ID:  " << (*itr)->getStuId() << endl;
        cout << "Course Code: " << (*itr)->getCode() << endl;
        cout << "Exam Mark:   " << (*itr)->getMark() << endl;
        
    }while(false);
    
    terminal->pause();
    return 0;
}
