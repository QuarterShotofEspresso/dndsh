all : bin/dndsh

bin/dndsh : build/main.o build/dndsh.o
	g++ -o bin/dndsh build/main.o build/dndsh.o -lreadline

build/main.o : src/main.cpp
	g++ -c -Wall -Iincludes -o build/main.o src/main.cpp

build/dndsh.o : src/dndsh.cpp
	g++ -c -Wall -Iincludes -o build/dndsh.o src/dndsh.cpp

clean :
	rm -rf build/* bin/*
