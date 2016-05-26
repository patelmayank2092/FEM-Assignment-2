
all: triangle main solve

solve: triangle.o main.o 
	g++ -o3 -std=c++11 triangle.o main.o -o solve

triangle: triangular.h triangular.cpp
	g++ -c -o3 -std=c++11 triangular.cpp -o triangle.o

main: type.h Vertex.h main.cpp
	g++ -c -o3 -std=c++11 main.cpp -o main.o


clean:
	rm -rf *.o
	rm solve
