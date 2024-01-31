# terminate upon error
set -e

cflags='-Isrc -std=c99'
cppflags='-Isrc -std=c++14'
cudaflags='-Isrc -std=c++14 -arch=sm_61'

echo "compiling CPU backend in C++..."
g++ -c src/core.cpp $cppflags -o core.o
g++ -c src/alts.cpp $cppflags -o alts.o

echo "compiling and linking CPU main in C++..."
g++ main.cpp core.o alts.o $cppflags -o main_cpp
./main_cpp

echo "compiling and linking CPU main in C..."
gcc main.c core.o alts.o $cflags -o main_c
./main_c

echo "compiling GPU backend in C++..."
nvcc -c src/core.cu $cudaflags -o core.o
g++ -c src/alts.cpp $cppflags -o alts.o

echo "compiling GPU main in C++..."
g++ -c main.cpp $cppflags -o main.o

echo "linking GPU C++..."
nvcc main.o core.o alts.o $cudaflags -o main_cuda_cpp
./main_cuda_cpp

echo "compiling GPU main in C..."
gcc -c main.c $cflags -o main.o

echo "linking GPU C..."
nvcc main.o core.o alts.o $cudaflags -o main_cuda_c
./main_cuda_c