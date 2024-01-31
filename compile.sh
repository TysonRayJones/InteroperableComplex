
echo "compiling backend in C++..."
g++ -c src/core.cpp -Isrc -std=c++14 -o core.o

echo "compiling main in C++..."
g++ main.cpp core.o -Isrc -std=c++14 -o main_cpp
./main_cpp

echo "compiling main in C..."
gcc main.c core.o -Isrc -std=c99 -o main_c
./main_c