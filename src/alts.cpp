/*
 * This file contains C-friendly wrappers around the C++ functions
 * which cannot be directly called from C before they pass or receive
 * qcomp by-value. This file is always pre-compiled in C++ before 
 * compiling user code (in C or C++). Here, qcomp is always 
 * resolved to the C++ complex type. We disable name-mangling 
 * (via extern "C") so that a user's C code can use these functions.
 * These "alternatives" are defined here so that core.cpp (and
 * other backends, like core.cu) don't need to duplicate wrappers.
 */

#include "core.both"


// disable name-mangling so the below symbols, once compiled by the
// C++ compiler, are accessible to the c program
extern "C" {

    // C-friendly alternatives to the C++ funcs which handle qcomp values
    double myDoubleFunc_alt(qcomp* a) {
        return myDoubleFunc(*a);
    }
    void myCompFunc_alt(qcomp* out, qcomp *in) {
        *out = myCompFunc(*in);
    }

// end de-mangler
}