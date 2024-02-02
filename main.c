/*
 * This is a C user's main file. 
 * Here, qcomp is a C Complex type, with functions like creal & cimag.
 * This incidentally differs from the type that the (C++) compiler 
 * understood when compiling myCompFunc.
 */

#include <stdio.h>

#include "core.both"
#include "comm.both"
#include "multi.both"

int main() {
    
    // C MSVC users are cursed
    #if _MSC_VER
        qcomp arr[3] = {{0., 1.}, {2., 3.}, {1., 0.}};
        qcomp x = {1., 1.};
    #else
        qcomp arr[3] = {1.i, 2.+3.i, 1.};
        qcomp x = 1. + 1.i;
    #endif

    double z = myCompArrFunc(arr, 3);
    printf("z = %g\n", z);

    double r = myDoubleFunc(x);
    printf("r = %g\n", r);

    qcomp y = myCompFunc(x);
    printf("y = %g + i(%g)\n", creal(y), cimag(y));

    myCommFunc(arr, 3);

    myMultiFunc();

    return 0;
}