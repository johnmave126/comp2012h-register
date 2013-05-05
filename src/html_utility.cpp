/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * html_utility.cpp
 *
 * html generating utilities
 */

#include "html_utility.h"
#include "register_common.h"
#include "bootstrap.h"
#include "deque.h"
#include <cstring>

static const char header_first[] = 
"<!DOCTYPE html>\n"
"<html>\n"
"<head>\n";

static const char header_middle[] = 
"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n"
"<meta http-equiv=\"keyword\" content=\"register\" />\n"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />\n"
"<style type=\"text/css\" >\n";

static const char header_final[] = 
"</style>\n"
"</head>\n"
"<body>\n"
"<div class=\"header\">";

static const char html_final[] = 
"</div>\n"
"</body>\n"
"</html>\n"
"\n";

HTMLFile::HTMLFile()
:file(NULL), html_title(NULL), fstate(ready) {
    os.exceptions(ofstream::failbit | ofstream::badbit);
}

HTMLFile::~HTMLFile() {
    if(os.is_open()) {
        os.close();
    }
    if(file) {
        delete [] file;
    }
    if(html_title) {
        delete [] html_title;
    }
}

HTMLFile::HTMLFile(const char fileName[], const char title[])
:file(new char[strlen(fileName) + 1]),
 html_title(new char[strlen(title) + 1]),
 fstate(ready) {
    strcpy(file, fileName);
    strcpy(html_title, title);
    os.exceptions(ofstream::failbit | ofstream::badbit);
 }

void HTMLFile::begin() {
    if(!file || strlen(file) == 0) {
        throw "No file name specified";
    }
    os.open(file, ofstream::out | ofstream::trunc);

    fstate = opened;

    os << header_first;
    os << "<title>" << html_title << "</title>\n";
    os << header_middle;
    os << bootstrap_css;
    os << header_final;
    os << "<h3>HKUST Course Registration System</h3></div>\n";
    os << "<div class=\"wrap\">\n";
}

void HTMLFile::end() {
    if(fstate != opened) {
        throw "File is not opened";
    }
    if(!tag_stack.isEmpty()) {
        throw "Tag corrupted";
    }
    os << html_final;

    os.close();

    fstate = closed;
}

void HTMLFile::openTag(const char tagName[], const char className[]) {
    if(fstate != opened) {
        throw "File not opened";
    }
    if(!tagName || strlen(tagName) == 0) {
        throw "Empty Tag";
    }
    os << "<" << tagName << " ";
    if(className && strlen(className) > 0) {
        os << "class=\"" << className << "\"";
    }
    os << ">\n";

    tag_stack.addLast(tagName);
}

void HTMLFile::closeTag() {
    if(tag_stack.isEmpty()) {
        throw "Tag corrupted";
    }
    os << "\n</" << tag_stack.removeLast() << ">\n";
}

void HTMLFile::writeString(const char content[]) {
    os << content;
}
