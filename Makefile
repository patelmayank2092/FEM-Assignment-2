
all:	main initialisation matrix_generator solve

solve:	initialisation.o matrix_generator main.o
	g++ -O3 -std=c++11 initialisation.o matrix_generator.o main.o -o solve

initialisation:   initialisation.h initialisation.cpp
	g++ -c -O3 -std=c++11 initialisation.cpp -o initialisation.o

main:   type.h  Vertex.h initialisation.h matrix_generator.h main.cpp
	g++ -c -O3 -std=c++11 main.cpp -o main.o

matrix_generator: matrix_generator.h matrix_generator.cpp 
	g++ -c -O3 -std=c++11 matrix_generator.cpp -o matrix_generator.o

clean:
	rm -rf *.o
	rm solve
