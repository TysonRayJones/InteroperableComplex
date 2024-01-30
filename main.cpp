/*
 * This is a C++ user's main file. 
 * Here, qcomp is a C++ Complex type, with functions like real & imag.
 * This incidentally matches the type understood by the compiler when
 * compiling myCompFunc.
 */

#include <stdio.h>
#include "core.hpp"

int main() {

    qcomp x = qcomp(1,1);
    qcomp y = myCompFunc(x);

    printf("y = %g + i(%g)\n", real(x), imag(y));

    return 0;
}