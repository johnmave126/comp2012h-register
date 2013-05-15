/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * html_table.cpp
 *
 * support table of html
 */

#include "html_table.h"
#include "html_utility.h"
#include "register_common.h"
#include "deque.h"

#include <cstring>
#include <string>
#include <stdexcept>

using std::string;
using std::runtime_error;

HTMLTable::HTMLTable() {
    throw runtime_error("Using default constructor");
}

HTMLTable::~HTMLTable() {
}

HTMLTable::HTMLTable(HTMLFile *_file, string _title, bool index)
:file(_file),
 title(_title), fstate(ready),
 idx(index?(1):(0)) {
    if(file->getState() != HTMLFile::opened) {
        throw runtime_error("File not opened");
    }
}

void HTMLTable::insertHead(string _head) {
    if(fstate != ready) {
        throw runtime_error("Cannot insert head at this state");
    }
    //Add to heads
    heads.addLast(_head);
}

void HTMLTable::begin() {
    int i;
    Deque<string>::Iterator itr(heads);
    if(fstate != ready) {
        throw runtime_error("Cannot insert head at this state");
    }
    //The open of a table
    file->openTag("table", "table table-striped table-hover");
    file->openTag("caption");
    file->writeString(title);
    file->closeTag();
    //Writing head 
    file->openTag("thead");
    file->openTag("tr");
    if(idx) {
        file->openTag("th");
        file->writeString("#");
        file->closeTag();
    }
    for(i = 0; i < heads.size(); i++, ++itr) {
        file->openTag("th");
        file->writeString(*itr);
        file->closeTag();
    }
    file->closeTag();
    file->closeTag();
}

void HTMLTable::end() {
    if(fstate != opened) {
        throw runtime_error("File is not opened");
    }
    file->closeTag();

    fstate = closed;
}

void HTMLTable::beginRow() {
    char buff[16];
    if(fstate != opened) {
        throw runtime_error("Cannot insert row at this state");
    }
    file->openTag("tr");
    //Insert a index field if necessary
    if(idx > 0) {
        sprintf(buff, "%d", idx);
        insertCell(buff);
    }
}

void HTMLTable::endRow() {
    if(fstate != opened) {
        throw runtime_error("Cannot end row at this state");
    }
    file->closeTag();
    //Increase index
    idx++;
}

void HTMLTable::insertCell(string content) {
    file->openTag("td");
    file->writeString(content);
    file->closeTag();
}
