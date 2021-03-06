CC=gcc
CPP=g++
LINK=g++
LFLAGS=-fstack-protector
LIBS=
AR=ar
RM=rm
CP=cp
INCPATH=-Iinclude -I.
CFLAGS=-O3 -Wextra -Wall -fexceptions -fstack-protector -Wno-unused-parameter
CPPFLAGS=$(CFLAGS)
MAKE=make

TMP_PATH=build_tmp
BIN_PATH=build_bin

HEADERS = include/bootstrap.h \
		include/html_utility.h \
		include/html_table.h \
		include/deque.h \
		include/sortlist.h \
		include/register_common.h \
		include/term_utility.h \
		include/hashmap.h \
		include/register_menu.h \
		include/regular_expression.h \
		include/register_verifier.h \
		include/register_student.h \
		include/register_course.h \
		include/register_course_selection.h \
		include/register_system.h
SOURCES = src/html_utility.cpp \
		src/html_table.cpp \
		src/term_utility.cpp \
		src/register.cpp \
		src/register_menu.cpp \
		src/regular_expression.cpp \
		src/register_verifier.cpp \
		src/register_common.cpp \
		src/register_student.cpp \
		src/register_course.cpp \
		src/register_course_selection.cpp \
		src/register_system.cpp \
		src/register_student_management.cpp \
		src/register_course_management.cpp \
		src/register_course_registration.cpp \
		src/register_report_management.cpp \
		src/register_file_management.cpp
OBJECTS = build_tmp/html_utility.o \
		build_tmp/html_table.o \
		build_tmp/term_utility.o \
		build_tmp/register.o \
		build_tmp/register_menu.o \
		build_tmp/regular_expression.o \
		build_tmp/register_verifier.o \
		build_tmp/register_common.o \
		build_tmp/register_student.o \
		build_tmp/register_course.o \
		build_tmp/register_course_selection.o \
		build_tmp/register_system.o \
		build_tmp/register_student_management.o \
		build_tmp/register_course_management.o \
		build_tmp/register_course_registration.o \
		build_tmp/register_report_management.o \
		build_tmp/register_file_management.o

all: $(TMP_PATH)/Makefile.control $(BIN_PATH)/Register

$(BIN_PATH)/Register: $(OBJECTS)
	test -d $(BIN_PATH) || mkdir -p $(BIN_PATH)
	$(LINK) $(LFLAGS) -o $(BIN_PATH)/Register $(OBJECTS) $(LIBS)

build_tmp/html_utility.o: src/html_utility.cpp include/html_utility.h \
 include/deque.h include/bootstrap.h include/register_common.h
	test -d $(TMP_PATH) || mkdir -p $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/html_utility.o src/html_utility.cpp

build_tmp/html_table.o: src/html_table.cpp include/html_table.h \
 include/html_utility.h include/deque.h include/html_utility.h \
 include/register_common.h
	test -d $(TMP_PATH) || mkdir -p $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/html_table.o src/html_table.cpp

build_tmp/term_utility.o: src/term_utility.cpp include/term_utility.h \
 include/register_common.h
	test -d $(TMP_PATH) || mkdir -p $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/term_utility.o src/term_utility.cpp

build_tmp/register_menu.o: src/register_menu.cpp include/register_common.h \
 include/register_menu.h include/term_utility.h
	test -d $(TMP_PATH) || mkdir -p $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/register_menu.o src/register_menu.cpp

build_tmp/regular_expression.o: src/regular_expression.cpp \
 include/regular_expression.h include/register_common.h
	test -d $(TMP_PATH) || mkdir -p $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/regular_expression.o src/regular_expression.cpp

build_tmp/register_verifier.o: src/register_verifier.cpp include/register_common.h \
 include/register_verifier.h include/regular_expression.h include/hashmap.h \
 include/sortlist.h include/register_verifier.h
	test -d $(TMP_PATH) || mkdir -p $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/register_verifier.o src/register_verifier.cpp

build_tmp/register_common.o: src/register_common.cpp include/register_common.h
	test -d $(TMP_PATH) || mkdir -p $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/register_common.o src/register_common.cpp

build_tmp/register_student.o: src/register_student.cpp include/register_common.h \
 include/register_student.h
	test -d $(TMP_PATH) || mkdir -p $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/register_student.o src/register_student.cpp

build_tmp/register_course.o: src/register_course.cpp include/register_common.h \
 include/register_course.h
	test -d $(TMP_PATH) || mkdir -p $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/register_course.o src/register_course.cpp

build_tmp/register_course_selection.o: src/register_course_selection.cpp include/register_common.h \
 include/register_course_selection.h
	test -d $(TMP_PATH) || mkdir -p $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/register_course_selection.o src/register_course_selection.cpp

build_tmp/register_system.o: src/register_system.cpp include/register_common.h \
 include/register_system.h include/term_utility.h include/sortlist.h include/hashmap.h \
 include/register_verifier.h include/regular_expression.h \
 include/register_menu.h include/register_student.h \
 include/register_course.h include/register_course_selection.h 
	test -d $(TMP_PATH) || mkdir -p $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/register_system.o src/register_system.cpp

build_tmp/register_student_management.o: src/register_student_management.cpp \
 include/register_common.h include/register_system.h \
 include/term_utility.h include/sortlist.h include/hashmap.h \
 include/register_verifier.h include/regular_expression.h include/register_menu.h \
 include/register_student.h include/register_course.h \
 include/register_course_selection.h
	test -d $(TMP_PATH) || mkdir -p $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/register_student_management.o src/register_student_management.cpp

build_tmp/register_course_management.o: src/register_course_management.cpp \
 include/register_common.h include/register_system.h \
 include/term_utility.h include/sortlist.h include/hashmap.h \
 include/register_verifier.h include/regular_expression.h include/register_menu.h \
 include/register_student.h include/register_course.h \
 include/register_course_selection.h
	test -d $(TMP_PATH) || mkdir -p $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/register_course_management.o src/register_course_management.cpp

build_tmp/register_course_registration.o: src/register_course_registration.cpp \
 include/register_common.h include/register_system.h \
 include/term_utility.h include/sortlist.h include/hashmap.h \
 include/register_verifier.h include/regular_expression.h include/register_menu.h \
 include/register_student.h include/register_course.h \
 include/register_course_selection.h
	test -d $(TMP_PATH) || mkdir -p $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/register_course_registration.o src/register_course_registration.cpp

build_tmp/register_report_management.o: src/register_report_management.cpp \
 include/register_common.h include/register_system.h \
 include/term_utility.h include/sortlist.h include/hashmap.h \
 include/register_verifier.h include/regular_expression.h \
 include/register_menu.h include/register_student.h \
 include/register_course.h include/register_course_selection.h \
 include/deque.h include/html_table.h include/html_utility.h
	test -d $(TMP_PATH) || mkdir -p $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/register_report_management.o src/register_report_management.cpp

build_tmp/register_file_management.o: src/register_file_management.cpp \
 include/register_common.h include/register_system.h \
 include/term_utility.h include/sortlist.h \
 include/hashmap.h include/register_verifier.h \
 include/regular_expression.h include/register_menu.h \
 include/register_student.h include/register_course.h \
 include/register_course_selection.h
	test -d $(TMP_PATH) || mkdir -p $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/register_file_management.o src/register_file_management.cpp

build_tmp/register.o:  src/register.cpp include/register_common.h \
 include/term_utility.h include/register_system.h \
 include/sortlist.h include/hashmap.h include/register_verifier.h \
 include/regular_expression.h include/register_menu.h \
 include/register_student.h include/register_course.h \
 include/register_course_selection.h
	test -d $(TMP_PATH) || mkdir -p $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/register.o src/register.cpp

build_tmp/Makefile.control: Makefile
	test -d $(TMP_PATH) || mkdir -p $(TMP_PATH)
	touch $(TMP_PATH)/Makefile.control
	$(MAKE) clean
	$(MAKE) all

.PHONY: clean
clean:
	rm -f $(TMP_PATH)/*.o $(BIN_PATH)/*