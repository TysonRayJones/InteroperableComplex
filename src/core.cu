
#include <cuComplex.h>

#include "core.both"


// we have to define our own overloads, REEEE

typedef cuDoubleComplex cu_qcomp;

__host__ __device__ inline cu_qcomp operator + (const cu_qcomp& a, const cu_qcomp& b) {
    cu_qcomp res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    return res;
}


// here, we attempt to pass 'qcomp' straight to a 'cu_qcomp' argument.
// we expect this won't work; we will have to reinterpret_cast instead

__global__ void kernel_myDoubleFunc(cu_qcomp in, double* d_out){
    *d_out = in.x;
}

double myDoubleFunc(qcomp in) {

    double* d_out;
    cudaMalloc(&d_out, sizeof(double));

    cu_qcomp cu_in = reinterpret_cast<cu_qcomp&>(in);
    kernel_myDoubleFunc<<<1, 1>>>(cu_in, d_out);

    double out;
    cudaMemcpy(&out, d_out, sizeof(qcomp), cudaMemcpyDeviceToHost);
    cudaFree(d_out);
    return out;
}


// here, we copy a qcomp straight into a cu_qcomp
// pointer, and back. We expect this to work, because
// qcomp and cu_qcomp have the same memory layout

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
// we expect this to work; it is identical to the above situation, albeit we
// have more than one qcomp to copy

__global__ void kernel_myCompArrFunc(cu_qcomp* d_arr, int len, double* d_out) {
    *d_out = 0;
    for (int i=0; i<len; i++)
        *d_out += d_arr[i].x;
}

// disable name-mangling; this function be directly called by C

extern "C" double myCompArrFunc(qcomp* arr, int len) {

    cu_qcomp* d_arr;
    size_t mem = len * sizeof(qcomp);
    cudaMalloc(&d_arr, mem);
    cudaMemcpy(d_arr, arr, mem, cudaMemcpyHostToDevice);

    double* d_out;
    cudaMalloc(&d_out, sizeof(double));

    kernel_myCompArrFunc<<<1, 1>>>(d_arr, len, d_out);

    double out;
    cudaMemcpy(&out, d_out, size(double), cudaMemcpyDeviceToHost);
    cudaFree(d_arr);
    cudaFree(d_out);
    return a;
}


// we don't bother making a kernel for this uninteresting function.
// must disable name-mangling; this function be directly called by C

extern "C" int myIntFunc(int a) {
    return 2*a;
}

