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
#include "hashmap.h"
#include <iostream>
#include <stdexcept>

using std::cout;
using std::cin;
using std::endl;
using std::runtime_error;

static bool filter(int n) {
    return (n >= 4) && (n <= 8);
}

static bool greater(int a, int b) {
    return a > b;
}

static int cusHash(int n) {
    return n;
}

void test_suite1() {
    //Test the correctness of basic operation
    int i;
    Hashmap<int, int, int(*)(int)> q(cusHash, 30);
    Hashmap<int, int, int(*)(int)>::Iterator itr;
    
    cout << "Begin Test Suite 1:" << endl;
    
    q.insert(2,7);
    q.insert(31,3);
    q.insert(32,8);
    q.insert(6,10);
    q.insert(8,2);
    q.insert(39,1);
    q.insert(30,9);
    q.insert(2,4);
    q.insert(14,5);
    q.insert(6,6);
    
    itr = q.query(2);
    try {
        while(true) {
            cout << (*itr) << endl;
            itr++;
        }
    }
    catch(runtime_error& e) {
        //Ignore
    }
    cout << endl;
    /*
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
    */
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
