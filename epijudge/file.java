import java.util.*;
import java.io.*;

// can import test specific utilities

class Atest {

    public static void main(String[] args) {
        if (2 != A.sum(1,1)) {
            System.out.println("Atrocity! 2 != 1 + 1");
        }
    }

}


// This is the EPI program
// it will not compile like this because of the import just before class A.
//
// approach 1: have slava's program that generates the JSON for the post move the imports
// from the second program to the top
//
// approach 2: have the two programs sent by judge, and compilebox will compile both and
// execute the test one (Atest in this case). this has the benefit of compile errors
// matching line numbers in the users editor.
//
// if we use approach 2, then we should do the same for CPP

import java.util.*;

class A {
    // @fillme (this is used to add in the contributed program)
        // judge include
    static int sum(int a, int b) {
        // judge exclude
        return a + b;
        // judge include
    }
        // judge exclude


    public static void main(String[] args) {
        System.out.println(sum(1,1));
    }
}
