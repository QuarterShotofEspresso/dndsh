all : bin/dndsh

bin/dndsh : builds/main.o builds/dndsh.o
	g++ -o bin/dndsh builds/main.o builds/dndsh.o -lreadline

builds/main.o : src/main.cpp
	g++ -c -Wall -Iincludes -o builds/main.o src/main.cpp

builds/dndsh.o : src/dndsh.cpp
	g++ -c -Wall -Iincludes -o builds/dndsh.o src/dndsh.cpp

clean :
	rm -rf builds/* bin/*
