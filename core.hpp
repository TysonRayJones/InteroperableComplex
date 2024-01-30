/*
 * This C/C++ file is the backend header. It is parsed by a 
 * C++ compiler when compiling core.cpp, but it is also parsed 
 * by a C compiler when compiling user's C code. As such, the
 * referred 'qcomp' type is assumed to be the compiler's native
 * complex type.
 */

#ifndef CORE_HPP
#define CORE_HPP

// types.hpp is also a C/C++ agnostic file, so we can import it directly
#include "types.hpp"

// when this file is being parsed by C++, we disable its name mangling, so
// that a user's C code can later find these symbols
#ifdef __cplusplus
extern "C" {
#endif

    // both C and C++ agree on 'int' just fine; no issues
    int myIntFunc(int a);

    // the C++ compiler will warn that 'qcomp' (which it recognises as 
    // a C++ templated type) is not compatible with C, so should not be
    // in an extern "C". Because we know the type is the C++ complex type,
    // which has the same layout as C's complex type, we ignore it.
    // But beware... they may not have the same ABI in some compilers!
    qcomp myCompFunc(qcomp a);

// end de-mangler
#ifdef __cplusplus
}
#endif

#endif // CORE_HPP