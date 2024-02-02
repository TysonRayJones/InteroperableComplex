# terminate upon error
set -e

cflags='-Isrc -std=c99 -lstdc++ -Wall'
cppflags='-Isrc -std=c++14 -Wall'
cudaflags='-Isrc -std=c++14 -arch=sm_61 -Wall'


echo "compiling CPU backend in C++..."
g++ -c src/core.cpp $cppflags -o core.o
g++ -c src/alts.cpp $cppflags -o alts.o
g++ -c src/comm.cpp $cppflags -o comm.o

echo "compiling and linking CPU main in C++..."
g++ main.cpp core.o alts.o comm.o $cppflags -o main_cpp
./main_cpp

echo "compiling and linking CPU main in C..."
gcc main.c core.o alts.o comm.o $cflags -o main_c
./main_c


echo "deleting comm.o"
rm comm.o


echo "compiling distributed CPU backend in C++..."
mpic++ -c src/comm.cpp $cppflags -DDISTRIBUTED_MODE -o comm.o

echo "compiling and linking distributed CPU main in C++..."
mpic++ main.cpp core.o alts.o comm.o $cppflags -o main_distrib_cpp
mpirun -np 2 main_distrib_cpp

echo "compiling and linking distributed CPU main in C..."
mpicc main.c core.o alts.o comm.o $cflags -o main_distrib_c
mpirun -np 2 main_distrib_c


echo "deleting all"
rm *.o


echo "compiling GPU backend in C++..."
nvcc -c src/core.cu $cudaflags -o core.o
g++ -c src/alts.cpp $cppflags -o alts.o
g++ -c src/comm.o $cppflags -o comm.o

echo "compiling GPU main in C++..."
g++ -c main.cpp $cppflags -o main.o

echo "linking GPU C++..."
nvcc main.o core.o alts.o comm.o $cudaflags -o main_cuda_cpp
./main_cuda_cpp

echo "compiling GPU main in C..."
gcc -c main.c $cflags -o main.o

echo "linking GPU C..."
nvcc main.o core.o alts.o comm.o $cudaflags -o main_cuda_c
./main_cuda_c
