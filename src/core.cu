/*
 * This is the C++ CUDA backend, to be compiled with nvcc. 
 * Here, qcomp is always resolved to the C++ complex type,
 * but this cannot be used by kernels deployed to the device;
 * instead, we must use NVIDIA's cuComplex types (aliased to
 * cu_qcomp), which  thankfully have the same memory-layout as 
 * std::complex. This means we can pass pointers to qcomp and
 * cu_qcomp interchangeably, and even cast values back and 
 * forth via reinterpret_cast. We disable name-mangling on the
 * functions we intend to be directly callable by a C user.
 */

#include "core.both"


// create cu_qcomp as a device-friendly equivalent of qcomp

#include <cuComplex.h>

typedef cuDoubleComplex cu_qcomp;

// annoyingly, we must define the overloads ourself

__host__ __device__ inline cu_qcomp operator + (const cu_qcomp& a, const cu_qcomp& b) {
    cu_qcomp res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    return res;
}


// here, we  pass a 'qcomp' value straight to a 'cu_qcomp' argument,
// leveraging that their memory layouts are equivalent, via reinterpret_cast.
// Because the host function accepts a 'qcomp' directly, it is C++-callable
// only, so we do not disable name-mangling.

__global__ void kernel_myDoubleFunc(cu_qcomp in, double* d_out){
    *d_out = in.x;
}

double myDoubleFunc(qcomp in) {

    double* d_out;
    cudaMalloc(&d_out, sizeof(double));

    cu_qcomp cu_in = reinterpret_cast<cu_qcomp&>(in);
    kernel_myDoubleFunc<<<1, 1>>>(cu_in, d_out);

    double out;
    cudaMemcpy(&out, d_out, sizeof(double), cudaMemcpyDeviceToHost);
    cudaFree(d_out);
    return out;
}


// here, we memcpy a qcomp straight into a cu_qcomp, and back.
// this is fine because of their identical memory layouts.
// Because the host function accepts a 'qcomp' directly, it is C++-callable
// only, so we do not disable name-mangling.

__global__ void kernel_myCompFunc(cu_qcomp* d_a){
    *d_a = *d_a + *d_a;
}

qcomp myCompFunc(qcomp a) {
    
    cu_qcomp* d_a;
    cudaMalloc(&d_a, sizeof(qcomp));
    cudaMemcpy(d_a, &a, sizeof(qcomp), cudaMemcpyHostToDevice);

    kernel_myCompFunc<<<1, 1>>>(d_a);

    cudaMemcpy(&a, d_a, sizeof(qcomp), cudaMemcpyDeviceToHost);
    cudaFree(d_a);
    return a;
}


// here, we copy a host-memory qcomp-array to a device-memory cu_qcomp-array.
// this is equivalent to above, albeit copying multiple values. We disable
// name-mangling on the host code, because it is to be directly callable in C

__global__ void kernel_myCompArrFunc(cu_qcomp* d_arr, int len, double* d_out) {
    *d_out = 0;
    for (int i=0; i<len; i++)
        *d_out += d_arr[i].x;
}

extern "C" double myCompArrFunc(qcomp* arr, int len) {

    cu_qcomp* d_arr;
    size_t mem = len * sizeof(qcomp);
    cudaMalloc(&d_arr, mem);
    cudaMemcpy(d_arr, arr, mem, cudaMemcpyHostToDevice);

    double* d_out;
    cudaMalloc(&d_out, sizeof(double));

    kernel_myCompArrFunc<<<1, 1>>>(d_arr, len, d_out);

    double out;
    cudaMemcpy(&out, d_out, sizeof(double), cudaMemcpyDeviceToHost);
    cudaFree(d_arr);
    cudaFree(d_out);
    return out;
}


// we don't bother making a kernel for this uninteresting function.
// must disable name-mangling; this function be directly called by C

extern "C" int myIntFunc(int a) {
    return 2*a;
}

