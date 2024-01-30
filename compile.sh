
echo "compiling backend in C++..."
g++ -c core.cpp -std=c++14 -o core.o

echo "compiling main in C++..."
g++ main.cpp core.o -std=c++14 -o main_cpp
./main_cpp

echo "compiling main in C..."
gcc main.c core.o -std=c99 -o main_c
./main_c