g++ -O3 -march=native -c -std=c++0x evaluation.cpp
g++ -O3 -march=native -c -std=c++0x class.cpp
g++ -O3 -march=native -c -std=c++0x nextstate.cpp
g++ -O3 -march=native -c -std=c++0x main.cpp
g++ class.o evaluation.o nextstate.o main.o -o assign5
rm -rf *.o