/*
 * This is the C++ backend. It is always pre-compiled in C++ 
 * before compiling user code (in C or C++). Here, qcomp is always 
 * resolved to the C++ complex type. We disable name-mangling 
 * (via extern "C") so that a user's C code can use these functions.
 */

#include "core.both"


// functions which return the C++ type can only be directly by a
// C++ binary; we will define C-friendly alternatives for them below,
// which will be wrapped by C in the core header to achieve the same signature
qcomp myCompFunc(qcomp a) {
    return a + a;
}


// disable name-mangling so the below symbols, once compiled by a
// C++ compiler, can still be invoked within a C program
extern "C" {

    // C and C++ binaries agree on ints
    int myIntFunc(int a) {
        return 2*a;
    }

    // C binaries can pass qcomp to C++ binaries
    double myDoubleFunc(qcomp a) {
        return real(a);
    }

    // C-friendly alternative to myCompFunc, which C will wrap
    void myCompFunc_alt(qcomp* out, qcomp in) {
        *out = myCompFunc(in);
    }

// end de-mangler
}