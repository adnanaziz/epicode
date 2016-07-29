// this is the test harness, everthing we need to test the code under test
// goes here. it has its own main(). we build a single stand alone executable
// using g++ Atest.cpp

#include <iostream>
#include "testutils.h"
#include "A.h"

using namespace std;

extern int sum(int a, int b);

// potential name conflict with A.cpp, but we can change the names,
// and this issue is easy to detect.
void test() {
    utils_check_equal(2, sum(1,1));
}

int main(int argc, char** argv) {
    test();
    return 0;
}

// now we include the code under test, with its main redefined to avoid a conflict
#define main _main

#include "A.cpp"
