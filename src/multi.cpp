
#include "multi.both"

#include <vector>
#include <random>
#include <chrono>
#include <iostream>


#ifdef _OPENMP

    // obtain API so we can query the number of threads
    #include <omp.h>

    // inform OpenMP how to reduce qcomp (except on Windows REEEE)
    #ifndef _MSC_VER
        #pragma omp declare	reduction(+ : qcomp : omp_out += omp_in ) initializer( omp_priv = omp_orig )
    #endif

#endif



extern "C" void myMultiFunc() {

    int len = 10000000;
    std::vector<qcomp> arr(len);
    for (int i=0; i<len; i++)
        arr[i] = qcomp(
            rand()/(double) RAND_MAX, 
            rand()/(double) RAND_MAX);
    
    auto start = std::chrono::high_resolution_clock::now();

    qcomp sum = 0;
    for (int i=0; i<len; i++)
        sum += arr[i];

    auto stop = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "serial duration (ms): " << dur.count() << std::endl;

#ifdef _OPENMP

    start = std::chrono::high_resolution_clock::now();

    int numThreads;
    #pragma omp parallel shared(numThreads)
    numThreads = omp_get_num_threads();

    sum = 0;

#ifdef  _MSC_VER

    double sumRe = 0;
    double sumIm = 0;
    #pragma omp parallel for reduction(+:sumRe,sumIm)
    for (int i=0; i<len; i++) {
        sumRe += real(arr[i]);
        sumIm += imag(arr[i]);
    }
    sum = qcomp(sumRe, sumIm);

#else

    #pragma omp parallel for reduction(+:sum)
    for (int i=0; i<len; i++)
        sum += arr[i];

#endif

    stop = std::chrono::high_resolution_clock::now();
    dur = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "multithreaded (" << numThreads << " threads) duration (ms): " << dur.count() << std::endl;

#else

    std::cout << "(no multithreading)" << std::endl;

#endif
}