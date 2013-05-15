/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * register_student_management.cpp
 *
 * The student management part of RegisterSystem
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

int RegisterSystem::insertStudent() {
    string input;
    RegisterStudent student;
    do {
        //Get student id
        cout << "Enter the student ID: ";
        getline(cin, input);
        while(!verifier.verify("ID", input)) {
            cout << "Invalid input, re-enter again [student ID]: ";
            getline(cin, input);
        }
        //Check existence
        if(DataStudents[input]) {
            cout << "Student already exist" << endl;
            break;
        }
        student.setStuId(input);

        //Get student name
        cout << "Enter the student name: ";
        getline(cin, input);
        while(!verifier.verify("StuName", input)) {
            cout << "Invalid input, re-enter again [student name]: ";
            getline(cin, input);
        }
        student.setStuName(input);

        //Get student year
        cout << "Enter the student year [1-3]: ";
        getline(cin, input);
        while(!verifier.verify("Year", input)) {
            cout << "Invalid input, re-enter again [student year]: ";
            getline(cin, input);
        }
        student.setYear(input);

        //Get student gender
        cout << "Enter the student gender [M,F]: ";
        getline(cin, input);
        while(!verifier.verify("Gender", input)) {
            cout << "Invalid input, re-enter again [MF]: ";
            getline(cin, input);
        }
        student.setGender(input);

        //Insert the student
        DataStudents.insert(student.getStuId(), student);

        //Output success message
        cout << "Creation of student record successful" << endl;
    }while(false);

    terminal->pause();
    return 0;
}

int RegisterSystem::modifyStudent() {
    string input;
    RegisterStudent *student;
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

        //Get student name
        cout << "Enter the student name [" << student->getStuName() << "]: ";
        getline(cin, input);
        while(!verifier.verify("StuName", input)) {
            cout << "Invalid input, re-enter again [student name]: ";
            getline(cin, input);
        }
        student->setStuName(input);

        //Get student year
        cout << "Enter the student year [" << student->getYear() << "]: ";
        getline(cin, input);
        while(!verifier.verify("Year", input)) {
            cout << "Invalid input, re-enter again [student year]: ";
            getline(cin, input);
        }
        student->setYear(input);

        //Get student gender
        cout << "Enter the student gender [" << student->getGender() << "]: ";
        getline(cin, input);
        while(!verifier.verify("Gender", input)) {
            cout << "Invalid input, re-enter again [MF]: ";
            getline(cin, input);
        }
        student->setGender(input);

        //Output success message
        cout << "Modification of student record successful" << endl;
    }while(false);

    terminal->pause();
    return 0;
}

int RegisterSystem::deleteStudent() {
    string input;
    RegisterStudent* student;
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
        
        //Delete in Course Code index
        CourseSelectionID.apply(input, delCourseSelection());

        //Delete in Course ID index
        CourseSelectionID.remove(input);

        //Delete in Course SortList
        DataCourseSelections.remove(delStuId(input));

        //Delete in Student Database
        DataStudents.remove(input);

        //Output success message
        cout << "Deletion of student record successful" << endl;
    }while(false);
    
    terminal->pause();
    return 0;
}

int RegisterSystem::queryStudent() {
    string input;
    RegisterStudent *student;
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

        //Put information
        cout << endl;
        cout << "ID:     " << student->getStuId() << endl;
        cout << "Name:   " << student->getStuName() << endl;
        cout << "Year:   " << student->getYear() << endl;
        cout << "Gender: " << ((student->getGender() == "M")?("Male"):("Female")) << endl;
        
    }while(false);
    
    terminal->pause();
    return 0;
}
