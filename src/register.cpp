/*
 * Register for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * register.cpp
 *
 * main entry of the program
 */

#include "term_utility.h"
#include "register_common.h"
#include "sortlist.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

static bool filter(int n) {
    return (n >= 4) && (n <= 8);
}

static bool greater(int a, int b) {
    return a > b;
}

void test_suite1() {
    //Test the correctness of basic operation
    int i;
    SortList<int, bool(*)(int, int)> q(greater);
    SortList<int, bool(*)(int, int)>::Iterator itr;
    
    cout << "Begin Test Suite 1:" << endl;
    
    q.insert(7);
    q.insert(3);
    q.insert(8);
    q.insert(10);
    q.insert(2);
    q.insert(1);
    q.insert(9);
    q.insert(4);
    q.insert(5);
    q.insert(6);
    
    itr = q.iterator();
    cout << "deque: " << q.size() << endl;
    for(i = 0; i < q.size(); i++, ++itr) {
        cout << (*itr) << endl;
    }
    cout << endl;
    
    //Test removing
    q.remove<bool(*)(int)>(filter);
    
    itr = q.iterator();
    cout << "deque: " << q.size() << endl;
    for(i = 0; i < q.size(); i++, ++itr) {
        cout << (*itr) << endl;
    }
    cout << endl;

    q.remove();
    cout << "size: " << q.size() << endl;
    
    cout << "End Test Suite 1" << endl << endl;
}

int main(int argc, char **argv) {
    int k = 0;
    Term terminal;
    terminal.init();
    test_suite1();
    cin >> k;
    terminal.restore();
    return 0;
}
