/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * register_common.h
 *
 * header file for some common definition
 */

#ifndef _REGISTER_COMMON_H
#define _REGISTER_COMMON_H

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef NULL
#define NULL 0
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#define WIN_TERM
#endif

//An always return true function object
template<typename T>
class ReturnTrue {
    public:
        ReturnTrue(){}
        bool operator()(const T&) const{return true;}
};

#endif
