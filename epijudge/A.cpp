#include <iostream>
#include "A.h"

using namespace std;

int sum(int a, int b) {
    // @exclude-judge
    return a + b;
    // @include-judge
}

int main(int argc, char** argv) {
    cout << sum(1,1) << endl;
    return 0;
}
