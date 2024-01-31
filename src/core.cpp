/*
 * This is the C++ backend. It is always pre-compiled in C++ 
 * before compiling user code (in C or C++). Here, qcomp is always 
 * resolved to the C++ complex type. We disable name-mangling 
 * (via extern "C") so that a user's C code can use these functions.
 */

#include "core.both"


// functions which pass or return the C++ type by-value can only be called
// directly by a C++ binary; we define C-friendly alternatives for them in alts.cpp,
// which will be wrapped by C in the core header to achieve the same signature as here
qcomp myCompFunc(qcomp a) {
    return a + a;
}
double myDoubleFunc(qcomp a) {
    return real(a);
}


// disable name-mangling so the below symbols, once compiled by a
// C++ compiler, can still be invoked within a C program
extern "C" {

    // C and C++ binaries agree on ints
    int myIntFunc(int a) {
        return 2*a;
    }

    // pointers to qcomp(s) are okay
    double myCompArrFunc(qcomp* arr, int len) {
        double r = 0;
        for (int i=0; i<len; i++)
            r += real(arr[i]);
        return r;
    }

// end de-mangler
}