  Register
  ===============
  
  This is a project for COMP2012H, 2013 Spring, HKUST
  
  The main purpose is to create a student registration system
  
  The course web page:
      http://course.cse.ust.hk/comp2012h
      (CSD account required)
  
  Author
  ===============
  Name: TAN, Shuhao
  Student ID: 20090398
  ITSC: stanab
  
  How-to-compile-and-run
  ===============
  >gmake
  >./build_bin/register
  
  Technical Details
  ===============
  
  The build of this project involves the following tools:
      Sublime Text 2 (text editor)
      SecureCRT (ssh terminal)
      X-Win32 2012 (X11 server for windows)
      Git (manage code)
      GNU toolchain (compiler)
  
  Source file tree:
      Register
      |
      |--include
      |  |--deque.h
      |  |--hashmap.h
      |  |--html_table.h
      |  |--html_utility.h
      |  |--register_common.h
      |  |--register_course.h
      |  |--register_course_selection.h
      |  |--register_menu.h
      |  |--register_student.h
      |  |--register_system.h
      |  |--register_verifier.h
      |  |--regular_expression.h
      |  |--sortlist.h
      |  |--term_utility.h
      |
      |--src
      |  |--html_table.cpp
      |  |--html_utility.cpp
      |  |--register.cpp
      |  |--register_common.cpp
      |  |--register_course.cpp
      |  |--register_course_management.cpp
      |  |--register_course_registration.cpp
      |  |--register_course_selection.cpp
      |  |--register_file_management.cpp
      |  |--register_menu.cpp
      |  |--register_report_management.cpp
      |  |--register_student.cpp
      |  |--register_student_management.cpp
      |  |--register_system.cpp
      |  |--register_verifier.cpp
      |  |--regular_expression.cpp
      |  |--term_utility.cpp
      |
      |--Makefile
  
  Deviation from sample program
      The last item of the submenues are changed to "Go back to previous menu"
      If looking into the standard output on linux platform, there may be
      weird characters before and after the program. They are control sequence
      used to flush the console window.
      The HTML file generated contains many extra stuff to make it looks 
      prettier.
  
  Design of the project:
      I've been trying to make a generic system, so there are many extra
      features implemented

      To accomplish a better view of terminal, I use control sequence of
      POSIX standard to control the behaviour of terminal. This part is
      in term_utility.h/cpp

      To better wrap the generation of HTML, I include bootstrap and write
      a simple HTML generator. This part is in html_utility.h/cpp,
      html_table.h/cpp

      To make an extendable model of event and menus, I immitate from Qt, 
      and implement a simple event model. Also, I implement a 
      easy-extendable menu model. This part is in register_common.h/cpp,
      register_menu.h/cpp

      To make the validation of user-input data easier, I implement a 
      regular expression engine. This engine is somehow primitive, because
      it uses recursion instead of compiling to a finite automaton. Maybe
      later I will implement a better engine. This part is in
      regular_expression.h/cpp. I also wrap the verification in
      register_verifier.h/cpp

      The implementation of a robust hashmap and sortlist is a hard task. I
      met compilation error many times. I create a somehow generic one because
      I add support to function objects. But this adds the use of template.
      Sometimes when a compilation error happens, the usee of template may
      be a disaster.

      The three object is in register_student.h/cpp, register_course.h/cpp,
      register_course_selection.h/cpp respectively. These parts are rough, 
      for I transfer the responsibility to check to the system. So they 
      are merely a data container.

      The core is around register_system. The implementations for each menu
      are splited into 5 files (for there are 5 submenus). 

      The implementation for managing students, courses, course selections are
      relatively simple. To accomplish the report management, I add an extra 
      API to my hashmap. That is dump, and it is tricky.

      The real challenge comes from storing database and recover from it. I
      tended to use XML to store the data. But I met the trouble to write an
      XML parser. I wanted to use fles/bison to accomplish it but I found that
      I have not enough time to implement an XML parser. So I have to use a
      rather dense and plain data representation. However, I do add some check
      to ensure the validity of the file.

      Overall, this project is huge and it seems that I make it more huge. But
      it is meaningful to try integrate all the stuff together and make them
      work well.
  
  Enjoy!
    TAN, Shuhao

--- end of README ---