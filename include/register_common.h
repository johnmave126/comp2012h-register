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

#include <string>
using std::string;

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

//A prototype for event model
class RegisterObject {
    public:
        RegisterObject():parent(NULL), head(NULL) {}
        virtual ~RegisterObject() {
            _node *t = head, *p;
            //Clear children list
            while(t) {
                p = t;
                t = t->next;
                delete p->item;
                delete p;
            }
        }

        RegisterObject(RegisterObject* _parent):parent(_parent), head(NULL) {
            _node *t;
            if(parent) {
                t = new _node;
                //Add to parent's children list
                t->item = this;
                t->next = parent->head;
                parent->head = t;
            }
        }

        virtual int getId(string name) {return -1;}
        virtual int fire(int idx) {return 1;}
    protected:

        RegisterObject *parent;
        //A linked list of children
        struct _node {
            RegisterObject *item;
            _node *next;
        } *head;
};

#define REGISTER_EVENT(class)                   \
    public:                                     \
        typedef struct {                        \
            const char *name;                   \
            int(class::*fnc)();                 \
        }RegType;                               \
        static RegType methods[];               \
        virtual int getId(string name);         \
        virtual int fire(int id);

#define REGISTER_EVENT_FNC(class)               \
int class::getId(string name) {                 \
    int i;                                      \
    for(i = 0; methods[i].name; i++) {          \
        if(name == methods[i].name) {           \
            return i;                           \
        }                                       \
    }                                           \
    return -1;                                  \
}                                               \
int class::fire(int id) {                       \
    return (this->*(methods[id].fnc))();        \
}                                       

#endif
