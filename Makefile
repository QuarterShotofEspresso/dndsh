all : bin/dndterm

bin/dndterm : build/main.o
	g++ -o bin/dndterm build/main.o

build/main.o : src/main.cpp
	g++ -c -Wall -Iincludes -o build/main.o src/main.cpp

clean :
	rm -rf build/* bin/*
