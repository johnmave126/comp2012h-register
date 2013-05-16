/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * register_report_management.cpp
 *
 * The report management part of RegisterSystem
 */

#include "register_common.h"
#include "register_system.h"
#include "html_utility.h"
#include "html_table.h"
#include "hashmap.h"

#include <iostream>
#include <string>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::runtime_error;

int RegisterSystem::allStudents() {
    Hashmap<string, RegisterStudent, int(*)(const string&, int)>::Iterator_All itr;
    bool hasStu = true;
    try {
        HTMLFile file("Students.html", "All Students List");
        file.begin();
        file.openTag("h3");
        file.writeString("All Students List");
        file.closeTag();
        itr = DataStudents.dump();
        try{
            itr.operator*();
        }
        catch(runtime_error& e) {
            hasStu = false;
            file.openTag("p");
            file.writeString("No student found");
            file.closeTag();
        }
        if(hasStu) {
            HTMLTable table(&file);
            table.insertHead("Student ID");
            table.insertHead("Student Name");
            table.insertHead("Year");
            table.insertHead("Gender");
            table.begin();
            try {
                while(true) {
                    //Test validity
                    itr.operator*();
                    table.beginRow();
                    table.insertCell(itr->getStuId());
                    table.insertCell(itr->getStuName());
                    table.insertCell(itr->getYear());
                    table.insertCell((itr->getGender() == "M")?("Male"):("Female"));
                    table.endRow();
                    itr++;
                }
            }
            catch(runtime_error& e) {
                //Ignore
            }
            table.end();
        }
        file.end();
        cout << "Output Successful" << endl;
    }
    catch(...) {
        cout << "File error" << endl;
    }

    terminal->pause();
    return 0;
}

int RegisterSystem::allCourses() {
    Hashmap<string, RegisterCourse, int(*)(const string&, int)>::Iterator_All itr;
    bool hasCourse = true;
    try {
        HTMLFile file("Courses.html", "All Course List");
        file.begin();
        file.openTag("h3");
        file.writeString("All Course List");
        file.closeTag();
        itr = DataCourses.dump();
        try{
            itr.operator*();
        }
        catch(runtime_error& e) {
            hasCourse = false;
            file.openTag("p");
            file.writeString("No course found");
            file.closeTag();
        }
        if(hasCourse) {
            HTMLTable table(&file);
            table.insertHead("Course Code");
            table.insertHead("Course Name");
            table.insertHead("Credit");
            table.begin();
            try {
                while(true) {
                    //Test validity
                    itr.operator*();
                    table.beginRow();
                    table.insertCell(itr->getCode());
                    table.insertCell(itr->getCourseName());
                    table.insertCell(itr->getCredit());
                    table.endRow();
                    itr++;
                }
            }
            catch(runtime_error& e) {
                //Ignore
            }
            table.end();
        }
        file.end();
        cout << "Output Successful" << endl;
    }
    catch(...) {
        cout << "File error" << endl;
    }

    terminal->pause();
    return 0;
}

int RegisterSystem::listCourses() {
    spHasp::Iterator itr;
    bool hasCourse = true;
    RegisterStudent* student;
    RegisterCourse* course;
    string input;
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

        try {
            HTMLFile file( student->getStuId() + ".html", "Course Records for Student " + student->getStuId());
            file.begin();
            file.openTag("h3");
            file.writeString("Course Records for Student: ");
            file.writeString(student->getStuName());
            file.writeString(" (" + student->getStuId() + ")");
            file.closeTag();
            itr = CourseSelectionID.query(student->getStuId());
            try{
                itr.operator*();
            }
            catch(runtime_error& e) {
                hasCourse = false;
                file.openTag("p");
                file.writeString("No course taken");
                file.closeTag();
            }
            if(hasCourse) {
                HTMLTable table(&file);
                table.insertHead("Course Code");
                table.insertHead("Course Name");
                table.insertHead("Credit");
                table.insertHead("Exam Mark");
                table.begin();
                try {
                    while(true) {
                        //Test validity
                        itr.operator*();
                        table.beginRow();
                        table.insertCell((*itr)->getCode());
                        //Query course
                        course = DataCourses[(*itr)->getCode()];
                        table.insertCell(course->getCourseName());
                        table.insertCell(course->getCredit());
                        table.insertCell((*itr)->getMark());
                        table.endRow();
                        itr++;
                    }
                }
                catch(runtime_error& e) {
                    //Ignore
                }
                table.end();
            }
            file.end();
            cout << "Output Successful" << endl;
        }
        catch(...) {
            cout << "File error" << endl;
        }
    }while(false);

    terminal->pause();
    return 0;
}

int RegisterSystem::listStudents() {
    spHasp::Iterator itr;
    bool hasStudent = true;
    RegisterStudent* student;
    RegisterCourse* course;
    string input;
    do {
        //Get course id
        cout << "Enter the course Code: ";
        getline(cin, input);
        while(!verifier.verify("Code", input)) {
            cout << "Invalid input, re-enter again [course Code]: ";
            getline(cin, input);
        }
        //Check existence
        course = DataCourses[input];
        if(!course) {
            cout << "Course not exist" << endl;
            break;
        }

        try {
            HTMLFile file( course->getCode() + ".html", "Student Records for Course " + course->getCode());
            file.begin();
            file.openTag("h3");
            file.writeString("Student Records for Course: ");
            file.writeString(course->getCourseName());
            file.writeString(" (" + course->getCode() + ")");
            file.closeTag();
            itr = CourseSelectionCode.query(course->getCode());
            try{
                itr.operator*();
            }
            catch(runtime_error& e) {
                hasStudent = false;
                file.openTag("p");
                file.writeString("No student takes this course");
                file.closeTag();
            }
            if(hasStudent) {
                HTMLTable table(&file);
                table.insertHead("Student ID");
                table.insertHead("Student Name");
                table.insertHead("Year");
                table.insertHead("Gender");
                table.insertHead("Exam Mark");
                table.begin();
                try {
                    while(true) {
                        //Test validity
                        itr.operator*();
                        table.beginRow();
                        table.insertCell((*itr)->getStuId());
                        //Query student
                        student = DataStudents[(*itr)->getStuId()];
                        table.insertCell(student->getStuName());
                        table.insertCell(student->getYear());
                        table.insertCell((student->getGender() == "M")?("Male"):("Female"));
                        table.insertCell((*itr)->getMark());
                        table.endRow();
                        itr++;
                    }
                }
                catch(runtime_error& e) {
                    //Ignore
                }
                table.end();
            }
            file.end();
            cout << "Output Successful" << endl;
        }
        catch(...) {
            cout << "File error" << endl;
        }
    }while(false);

    terminal->pause();
    return 0;
}
