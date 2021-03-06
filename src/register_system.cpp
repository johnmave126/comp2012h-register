/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * register_system.cpp
 *
 * register system, main control unit
 */

#include "register_common.h"
#include "register_system.h"
#include "term_utility.h"
#include "sortlist.h"
#include "hashmap.h"
#include "register_verifier.h"
#include "register_menu.h"
#include "register_student.h"
#include "register_course.h"
#include "register_course_selection.h"

#include <iostream>
#include <string>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::runtime_error;

//Some functions used
int hashStuId(const string& id, int m) {
    int base = 1;
    int ans = 0;
    const char* str = id.c_str();
    while(*str) {
        ans += ((*str++) - '0') * base;
        base = (base * 10) % m;
        ans %= m;
    }
    return ans;
}

int hashCode(const string& code, int m) {
    int base = 1;
    int ans = 0;
    const char* str = code.c_str();
    while(*str) {
        if(isdigit(*str)) {
            ans += ((*str++) - '0') * base;
        }
        else {
            ans += ((*str++) - 'A' + 10) * base;
        }
        base = (base * 36) % m;
        ans %= m;
    }
    return ans;
}

bool cmpCSp(RegisterCourseSelection* const & a, RegisterCourseSelection* const & b) {
    return (*a) < (*b);
}

RegisterSystem::RegisterSystem() {
    throw runtime_error("Invalid call to default constructor");
}

RegisterSystem::~RegisterSystem() {
}

RegisterSystem::RegisterSystem(Term* _terminal)
:terminal(_terminal), 
 menu(terminal, NULL, "HKUST Course Registration System"),
 DataStudents(hashStuId, 29), DataCourses(hashCode, 17),
 CourseSelectionID(hashStuId, 31, cmpCSp), CourseSelectionCode(hashCode, 31, cmpCSp) {
    //Init verifiers
    init_verifier();
    //Init Menu
    init_menu();
}

void RegisterSystem::exec() {
    //Init Terminal
    terminal->init();
    //Execute menu
    menu.exec();
    //Restore Terminal
    terminal->restore();
}

void RegisterSystem::init_verifier() {
    //Student ID
    verifier.insert("ID", "^\\d{8}$");
    //Student Name
    verifier.insert("StuName", "^\\w[\\w \\.\\d]{0,31}$");
    //Student Year
    verifier.insert("Year", "^0*[123]$");
    //Student Gender
    verifier.insert("Gender", "^[MF]$");
    //Course Code
    verifier.insert("Code", "^\\C{4}[\\C\\d]{3,4}$");
    //Course Name
    verifier.insert("CourseName", "^[^ ].{0,49}$");
    //Course Credit
    verifier.insert("Credit", "^0*[012345]$");
    //Course Mark
    verifier.insert("Mark", "^0*(100|\\d{1,2})$");
    //Course Mark for import
    verifier.insert("MarkImport", "^(N/A|0*(100|\\d{1,2}))$");
}

void RegisterSystem::init_menu() {
    RegisterMenu *student_manager, *course_manager, *course_registration,
        *report_manager, *file_manager;

    //Creation of student management
    student_manager = new RegisterMenu(terminal, &menu, "HKUST Course Registration System  (Student Menu)");
    student_manager->insertItem("Insert Student Record", this, "insertStudent");
    student_manager->insertItem("Modify Student Record", this, "modifyStudent");
    student_manager->insertItem("Delete Student Record", this, "deleteStudent");
    student_manager->insertItem("Query Student Record", this, "queryStudent");
    menu.insertItem("Student Management", student_manager);

    //Creation of course management
    course_manager = new RegisterMenu(terminal, &menu, "HKUST Course Registration System  (Course Menu)");
    course_manager->insertItem("Insert Course Record", this, "insertCourse");
    course_manager->insertItem("Modify Course Record", this, "modifyCourse");
    course_manager->insertItem("Delete Course Record", this, "deleteCourse");
    course_manager->insertItem("Query Course Record", this, "queryCourse");
    menu.insertItem("Course Management", course_manager);

    //Creation of course registration
    course_registration = new RegisterMenu(terminal, &menu, "HKUST Course Registration System  (Registration Menu)");
    course_registration->insertItem("Add Course", this, "addCourse");
    course_registration->insertItem("Drop Course", this, "dropCourse");
    course_registration->insertItem("Modify Exam Mark", this, "modifyExamMark");
    course_registration->insertItem("Query Registration", this, "queryRegistration");
    menu.insertItem("Course Registration", course_registration);

    //Creation of report management
    report_manager = new RegisterMenu(terminal, &menu, "HKUST Course Registration System  (Report Generation Menu)");
    report_manager->insertItem("List all student information", this, "allStudents");
    report_manager->insertItem("List all course information", this, "allCourses");
    report_manager->insertItem("List all courses of a student", this, "listCourses");
    report_manager->insertItem("List all students of a course", this, "listStudents");
    menu.insertItem("Report Management", report_manager);

    //Creation of file management
    file_manager = new RegisterMenu(terminal, &menu, "HKUST Course Registration System  (File Menu)");
    file_manager->insertItem("Save Database", this, "saveData");
    file_manager->insertItem("Load Database", this, "loadData");
    menu.insertItem("File Management", file_manager);
}

RegisterSystem::RegType RegisterSystem::methods[] = {
    {"insertStudent", &RegisterSystem::insertStudent},
    {"modifyStudent", &RegisterSystem::modifyStudent},
    {"deleteStudent", &RegisterSystem::deleteStudent},
    {"queryStudent", &RegisterSystem::queryStudent},

    {"insertCourse", &RegisterSystem::insertCourse},
    {"modifyCourse", &RegisterSystem::modifyCourse},
    {"deleteCourse", &RegisterSystem::deleteCourse},
    {"queryCourse", &RegisterSystem::queryCourse},

    {"addCourse", &RegisterSystem::addCourse},
    {"dropCourse", &RegisterSystem::dropCourse},
    {"modifyExamMark", &RegisterSystem::modifyExamMark},
    {"queryRegistration", &RegisterSystem::queryRegistration},

    {"allStudents", &RegisterSystem::allStudents},
    {"allCourses", &RegisterSystem::allCourses},
    {"listCourses", &RegisterSystem::listCourses},
    {"listStudents", &RegisterSystem::listStudents},

    {"saveData", &RegisterSystem::saveData},
    {"loadData", &RegisterSystem::loadData},
    {0, 0}
};
REGISTER_EVENT_FNC(RegisterSystem)
