/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * regular_expression.cpp
 *
 * a simple regular expression engine
 */

#include "regular_expression.h"
#include <cstring>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>

using std::string;
using std::vector;

//Handy function to deal with parenthesis
static const char* go_through_pa(const char* str) {
    while(*str && ( *str != ')' || *(str - 1) == '\\' )) {
        if(*str == '(' && *(str - 1) != '\\') {
            str = go_through_pa(str + 1);
        }
        else {
            str++;
        }
    }
    return (*str)?(str + 1):(str);
}

RegExp::RegExp()
:Re("") {
}

RegExp::~RegExp(){
}

RegExp::RegExp(string _r)
:Re(_r) {
}

RegExp::RegExp(const RegExp& r)
:Re(r.Re) {
}

RegExp& RegExp::operator=(const RegExp& r) {
    Re = r.Re;
    return (*this);
}

bool RegExp::match(string& str) {
    return match(str.c_str());
}

bool RegExp::match(const char *str) {
    if(Re[0] == '^') {
        return matchhere(Re.c_str() + 1, str);
    }
    do {
        if(matchhere(Re.c_str(), str))
            return true;
    }while(*str++ != '\0');
    return false;
}

bool RegExp::matchhere(const char *regex, const char *str) {
    int cur_type;
    //0 for simple character, 1 for special, 2 for [c], 3 for (v)
    char c; 
    string s;
    vector<string> v;
    vector<string>::iterator itr;
    char *end;
    long int a, b;
    const char* last_seg;

    //Check the first character
    switch(regex[0]) {
        case '\0':
            return true;
        case '\\':
            cur_type = 1;
            c = regex[1];
            if(!regex[1]) {
                return false;
            }
            regex += 2;
            break;
        case '[':
            cur_type = 2;
            regex++;
            while(*regex && (*regex != ']' || *(regex - 1) == '\\')) {
                if(regex[0] == '\0') {
                    return false;
                }
                s.push_back(regex[0]);
                regex++;
            }
            if(!*regex) {
                return false;
            }
            regex++;
            break;
        case '(':
            cur_type = 3;
            regex++;
            last_seg = regex;
            while(*regex && (*regex != ')' || *(regex - 1) == '\\')) {
                if(*regex == '(' && *(regex - 1) != '\\') {
                    regex = go_through_pa(regex + 1);
                }
                else if(*regex == '|' && *(regex - 1) != '\\' ) {
                    v.push_back(string(last_seg, regex - last_seg));
                    last_seg = regex + 1;
                    regex++;
                }
                else {
                    regex++;
                }
            }
            if(!*regex) {
                return false;
            }
            v.push_back(string(last_seg, regex - last_seg));
            regex++;
            break;
        default: 
            cur_type = 0;
            c = regex[0];
            regex++;
            break;
    }
    switch(regex[0]) {
        case '*':
            switch(cur_type) {
                case 0:
                //Simple
                    return matchstar(regex + 1, c, str);
                case 1:
                //special char
                    return matchstar_s(regex + 1, c, str);
                case 2:
                //[] type
                    return matchstar(regex + 1, s, str);
            }
            break;
        case '{':
            //{int} or {min,max}
            a = strtol(regex + 1, &end, 10);
            switch(end[0]) {
                case '}':
                //exactly type
                    switch(cur_type) {
                        case 0:
                        //Simple
                            return matchexactly(end + 1, c, a, str);
                        case 1:
                        //special char
                            return matchexactly_s(end + 1, c, a, str);
                        case 2:
                        //[] type
                            return matchexactly(end + 1, s, a, str);
                    }
                    break;
                case ',':
                //min max type
                    b = strtol(end + 1, &end, 10);
                    if(end[0] != '}'){
                        //invalid
                        return false;
                    }
                    switch(cur_type) {
                        case 0:
                        //Simple
                            return matchminmax(end + 1, c, a, b, str);
                        case 1:
                        //special char
                            return matchminmax_s(end + 1, c, a, b, str);
                        case 2:
                        //[] type
                            return matchminmax(end + 1, s, a, b, str);
                    }
                default:
                //invalid
                    return false;
            }
        default:
        //here match
            switch(cur_type) {
                case 0:
                //Simple
                    if(c == '$') {
                        return !regex[0] && !str[0];
                    }
                    if(str[0] && (c == '.' || c == str[0])) {
                        return matchhere(regex, str + 1);
                    }
                    return false;
                case 1:
                //special char
                    if(str[0] && testcharacter(c, str[0])) {
                        return matchhere(regex, str + 1);
                    }
                    return false;
                case 2:
                //[] type
                    if(str[0] && testcharacter(s, str[0])) {
                        return matchhere(regex, str + 1);
                    }
                    return false;
                case 3:
                //() type
                    for(itr = v.begin(); itr != v.end(); itr++) {
                        *itr += regex;
                        if(matchhere(itr->c_str(), str)) {
                            return true;
                        }
                    }
                    return false;
            }
    }
    return false;
}

bool RegExp::matchstar(const char *regex, char c, const char *str) {
    do {
        if(matchhere(regex, str)) {
            return true;
        }
    }while(*str && (*str++ == c || c == '.'));
    return false;
}

bool RegExp::matchstar(const char *regex, string c, const char *str) {
    do {
        if(matchhere(regex, str)) {
            return true;
        }
    }while(*str && testcharacter(c, *str++));
    return false;
}

bool RegExp::matchstar_s(const char *regex, char c, const char *str) {
    do {
        if(matchhere(regex, str)) {
            return true;
        }
    }while(*str && testcharacter(c, *str++));
    return false;
}

bool RegExp::matchexactly(const char *regex, char c, int time, const char *str) {
    while(time) {
        if(!str[0] || (*str++ != c && c != '.')) {
            return false;
        }
        time--;
    }
    return matchhere(regex, str);
}

bool RegExp::matchexactly(const char *regex, string c, int time, const char *str) {
    while(time) {
        if(!str[0] || !testcharacter(c, *str++)) {
            return false;
        }
        time--;
    }
    return matchhere(regex, str);
}

bool RegExp::matchexactly_s(const char *regex, char c, int time, const char *str) {
    while(time) {
        if(!str[0] || !testcharacter(c, *str++)) {
            return false;
        }
        time--;
    }
    return matchhere(regex, str);
}

bool RegExp::matchminmax(const char *regex, char c, int min, int max, const char *str) {
    max -= min;
    while(min) {
        if(!str[0] || (*str++ != c && c != '.')) {
            return false;
        }
        min--;
    }
    do {
        if(matchhere(regex, str)) {
            return true;
        }
    }while(*str && (*str++ == c || c == '.') && max--);
    return false;
}

bool RegExp::matchminmax(const char *regex, string c, int min, int max, const char *str) {
    max -= min;
    while(min) {
        if(!str[0] || !testcharacter(c, *str++)) {
            return false;
        }
        min--;
    }
    do {
        if(matchhere(regex, str)) {
            return true;
        }
    }while(*str && testcharacter(c, *str++) && max--);
    return false;
}

bool RegExp::matchminmax_s(const char *regex, char c, int min, int max, const char *str) {
    max -= min;
    while(min) {
        if(!str[0] || !testcharacter(c, *str++)) {
            return false;
        }
        min--;
    }
    do {
        if(matchhere(regex, str)) {
            return true;
        }
    }while(*str && testcharacter(c, *str++) && max--);
    return false;
}

bool RegExp::testcharacter(char s, char c) {
    switch(s) {
        case 'd':
            //0-9
            return isdigit(c);
        case 's':
            //whitespace
            return isspace(c);
        case 'w':
            //alphanumeric
            return isupper(c) || islower(c);
        case 'c':
            //non-capitalized
            return islower(c);
        case 'C':
            //Captitalized
            return isupper(c);

        //explicit definitions
        case '^':
        case '$':
        case '\\':
        case '.':
        case '[':
        case ']':
        case '{':
        case '}':
        case '|':
        case '(':
        case ')':
            return c == s;
        default:
            //invalid
            return false;
    }
    return false;
}

bool RegExp::testcharacter(string s, char c) {
    const char *str = s.c_str();
    bool flag = false;
    if(s[0] == '^') {
        str++;
        flag = true;
    }
    while(*str) {
        if(*str == '\\') {
            if(testcharacter(str[1], c)) {
                return true && !flag;
            }
            str += 2;
        }
        else {
            if(*str == c) {
                return true && !flag;
            }
            str++;
        }
    }
    return false || flag;
}
