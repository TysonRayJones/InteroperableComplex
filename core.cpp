/*
 * This is the C++ backend. It is always pre-compiled in C++ 
 * before compiling user code (in C or C++). Here, qcomp is always 
 * resolved to the C++ complex type. We disable name-mangling 
 * (via extern "C") so that a user's C code can use these functions.
 */

#include "core.hpp"

// disable name-mangling so the below symbols, once compiled by a
// C++ compiler, can still be invoked within a C program
extern "C" {

    int myIntFunc(int a) {
        return 2*a;
    }

    qcomp myCompFunc(qcomp a) {
        return a + a;
    }

// end de-mangler
}