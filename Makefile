
all:	main initialisation	solve

solve:	initialisation.o	main.o
	g++ -O3 -std=c++11 initialisation.o main.o -o solve

initialisation:   initialisation.h initialisation.cpp
	g++ -c -O3 -std=c++11 initialisation.cpp -o initialisation.o

main:   type.h  Vertex.h    main.cpp
	g++ -c -O3 -std=c++11 main.cpp -o main.o


clean:
	rm -rf *.o
	rm solve
