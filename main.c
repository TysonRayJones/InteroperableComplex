/*
 * This is a C user's main file. 
 * Here, qcomp is a C Complex type, with functions like creal & cimag.
 * This incidentally differs from the type that the (C++) compiler 
 * understood when compiling myCompFunc.
 */

#include <stdio.h>
#include "core.both"

int main() {

    qcomp x = 1 + 1i;
    qcomp y = myCompFunc(x);

    printf("y = %g + i(%g)\n", creal(x), cimag(y));

    return 0;
}