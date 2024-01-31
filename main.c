/*
 * This is a C user's main file. 
 * Here, qcomp is a C Complex type, with functions like creal & cimag.
 * This incidentally differs from the type that the (C++) compiler 
 * understood when compiling myCompFunc.
 */

#include <stdio.h>
#include "core.both"

int main() {

    qcomp arr[3] = {1.i, 2.+3.i, 1.};
    double z = myCompArrFunc(arr, 3);
    printf("z = %g\n", z);

    qcomp x = 1. + 1.i;
    double r = myDoubleFunc(x);
    printf("r = %g\n", r);

    qcomp y = myCompFunc(x);
    printf("y = %g + i(%g)\n", creal(y), cimag(y));

    return 0;
}