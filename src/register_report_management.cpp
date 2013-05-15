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
            file.writeString("No student found");
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

