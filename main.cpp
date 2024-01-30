/*
 * This is a C++ user's main file. 
 * Here, qcomp is a C++ Complex type, with functions like real & imag.
 * This incidentally matches the type understood by the compiler when
 * compiling myCompFunc.
 */

#include <stdio.h>
#include "core.both"

int main() {

    qcomp x = 1. + 1.i;
    double r = myDoubleFunc(x);
    printf("r = %g\n", r);

    qcomp y = myCompFunc(x);
    printf("y = %g + i(%g)\n", real(y), imag(y));

    return 0;
}