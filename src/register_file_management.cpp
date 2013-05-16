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
#include "hashmap.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::runtime_error;

int RegisterSystem::saveData() {
    Hashmap<string, RegisterStudent, int(*)(const string&, int)>::Iterator_All itr_student;
    Hashmap<string, RegisterCourse, int(*)(const string&, int)>::Iterator_All itr_course;
    SortList<RegisterCourseSelection>::Iterator itr_selection;
    ofstream output_file;
    string fileName;
    char buff[16];
    int tmp, i;
    //Set exception level
    output_file.exceptions(ofstream::failbit | ofstream::badbit);
    try {
        cout << "Enter the filename: ";
        getline(cin, fileName);
        output_file.open(fileName.c_str(), ofstream::out | ofstream::trunc);
        PACK_NUMBER(0x077CB531U, buff)
        output_file.write(buff, 4);

        //Write number of students
        tmp = DataStudents.size();
        PACK_NUMBER(tmp, buff)
        output_file.write(buff, 4);
        //Write students
        itr_student = DataStudents.dump();
        for(i = 0; i < tmp; i++, ++itr_student) {
            itr_student->serialize(output_file);
        }

        //Write number of courses
        tmp = DataCourses.size();
        PACK_NUMBER(tmp, buff)
        output_file.write(buff, 4);
        //Write courses
        itr_course = DataCourses.dump();
        for(i = 0; i < tmp; i++, ++itr_course) {
            itr_course->serialize(output_file);
        }

        //Write number of course selections
        tmp = DataCourseSelections.size();
        PACK_NUMBER(tmp, buff)
        output_file.write(buff, 4);
        //Write course selections
        itr_selection = DataCourseSelections.iterator();
        for(i = 0; i < tmp; i++, ++itr_selection) {
            itr_selection->serialize(output_file);
        }

        output_file.close();

        //Output success message
        cout << "Saving Successful" << endl;
    }
    catch(...) {
        cout << "Error: Write File Error" << endl;
    }

    terminal->pause();
    return 0;
}

int RegisterSystem::loadData() {
    Hashmap<string, RegisterStudent, int(*)(const string&, int)> tmp_student(hashStuId, 29);
    Hashmap<string, RegisterCourse, int(*)(const string&, int)> tmp_course(hashCode, 17);
    SortList<RegisterCourseSelection> tmp_selection;
    SortList<RegisterCourseSelection>::Iterator t_itr;
    spHasp tmp_ID(hashStuId, 31, cmpCSp);
    spHasp::Iterator itr;
    ifstream input_file;
    string fileName, input;
    RegisterStudent *student;
    RegisterCourse *course;
    RegisterStudent new_student;
    RegisterCourse new_course;
    RegisterCourseSelection new_selection;
    RegisterCourseSelection *refSelection;
    char buff[16];
    int i;
    unsigned int tmp;
    //Set exception level
    input_file.exceptions(ofstream::failbit | ofstream::badbit);

    try {
        cout << "Enter the filename: ";
        getline(cin, fileName);
        input_file.open(fileName.c_str(), ofstream::in);

        input_file.read(buff, 4);
        if(UNPACK_NUMBER(buff) != 0x077CB531U) {
            //Error
            throw 0;
        }
        //Read number of students
        input_file.read(buff, 4);
        tmp = UNPACK_NUMBER(buff);
        for(i = 0; i < static_cast<int>(tmp); i++) {
            new_student.recover(input_file);
            //Check data validity
            if(!(
              verifier.verify("ID", new_student.getStuId())
              && verifier.verify("StuName", new_student.getStuName())
              && verifier.verify("Year", new_student.getYear())
              && verifier.verify("Gender", new_student.getGender())
            )) {
                //Error
                throw 0;
            }
            //Check student existence
            student = tmp_student[new_student.getStuId()];
            if(student) {
                //Error
                throw 0;
            }
            //Insert into student table
            tmp_student.insert(new_student.getStuId(), new_student);
        }

        //Read number of courses
        input_file.read(buff, 4);
        tmp = UNPACK_NUMBER(buff);
        for(i = 0; i < static_cast<int>(tmp); i++) {
            new_course.recover(input_file);
            //Check data validity
            if(!(
              verifier.verify("Code", new_course.getCode())
              && verifier.verify("CourseName", new_course.getCourseName())
              && verifier.verify("Credit", new_course.getCredit())
            )) {
                //Error
                throw 0;
            }
            //Check student existence
            course = tmp_course[new_course.getCode()];
            if(course) {
                //Error
                throw 0;
            }
            //Insert into student table
            tmp_course.insert(new_course.getCode(), new_course);
        }

        //Read number of course selections
        input_file.read(buff, 4);
        tmp = UNPACK_NUMBER(buff);
        for(i = 0; i < static_cast<int>(tmp); i++) {
            new_selection.recover(input_file);
            //Check data validity
            if(!(
              verifier.verify("ID", new_selection.getStuId())
              && verifier.verify("Code", new_selection.getCode())
              && verifier.verify("MarkImport", new_selection.getMark())
            )) {
                //Error
                throw 0;
            }
            
            itr = tmp_ID.query(new_selection.getStuId());
            try {
                while(true) {
                    if((*itr)->getCode() == new_selection.getCode()) {
                        break;
                    }
                    itr++;
                }
                //Duplicate
                throw 0;
            }
            catch(runtime_error& e) {
                //Ignore
            }
            
            //Insert into sortlist
            refSelection = tmp_selection.insert(new_selection);
            
            //Insert into hashtable
            tmp_ID.insert(new_selection.getStuId(), refSelection);
        }

        input_file.close();
        //Cover the current database
        DataStudents = tmp_student;
        DataCourses = tmp_course;
        DataCourseSelections = tmp_selection;

        //Clear hash indices
        CourseSelectionID = spHasp(hashStuId, 31, cmpCSp);
        CourseSelectionCode = spHasp(hashCode, 31, cmpCSp);

        //Re-insert into indices
        t_itr = DataCourseSelections.iterator();
        for(i = 0; i < DataCourseSelections.size(); i++, ++t_itr) {
            CourseSelectionID.insert(t_itr->getStuId(), &(*t_itr));
            CourseSelectionCode.insert(t_itr->getCode(), &(*t_itr));
        }

        //Output success message
        cout << "Loading Successful" << endl;
    }
    catch(...) {
        cout << "Error: Load File Error (File not exist / File Corrupted / Incorrect Format)" << endl;
    }

    terminal->pause();
    return 0;
}
