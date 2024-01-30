Our goal is to create a `C++` library which handles complex numbers aliased as `qcomp`, which can be used directly by both `C++` and `C` user codes.
The challenge is that while the `C++` library is compiled with `qcomp = std::complex<double>` (the type provided by `<complex>`), 
the `C` user's code will understand `qcomp` as a `double complex` (provided by `<complex.h>`).

Our requirements are:
- the library backend and the user codes all use the same type alias; `qcomp`
- the library backend is always compiled as `C++` by a `C++` compiler
- the library backend always understands `qcomp` as `std::complex<double>` (regardless of the user's language)
- a `C++` user can pass `qcomp`'s of underlying type `std::complex<double>` to/from the library
- a `C` user can pass `qcomp`'s of underlying type `double complex` to/from the library

This repo contains files:
- `types.both` which defines `qcomp = std::complex<double>` (`C++` type) or `qcomp = double complex` (`C` type)
- `core.both` which declares function `myCompFunc`, which takes and accepts `qcomp`
- `core.cpp` which defines function `myCompFunc`, wherein `qcomp` is assumed to be `std::complex<double>` (`C++` type)
- `main.cpp` which is an example `C++` user's code
- `main.c` which is an example `C` user's code
- `compile.sh` which compiles both user's code

The proposed solution assumes that `std::complex<double>` and `double complex` have identical layouts. 
- we first compile the backend in `C++` (wherein `qcomp` is the `C++` type)
- we compile the user's `C++` code, trivially, wherein `qcomp` is the `C++` type
- we compile the user's `C` code, wherein `qcomp` is the `C` type
- both user codes parse `core.both`, wherein `qcomp` is ambiguous and is resolved to the compiler's native type
- `types.both` is parsed by both `C++` and `C`, which explicitly resolves `qcomp` to the compiler's native type

In essence:
- user's code uses the native type of their language (`C` vs `C++`)
- the backend always uses the `C++` type
- the user's `C` code is "tricked" into believing the backend used the `C` type

Issues:
- issues compiler warning
- may issue error on some compilers, like [MSVC](https://www.reddit.com/r/cpp/comments/xrno6a/c_and_c_complex_number_interoperability/)
- while the layouts might be the same, we pass `qcomp` across the ABI which doesn't seem gauranteed to agree. Might this code just silently fail at runtime?!

