all : bin/dndsh

bin/dndsh : build/main.o build/character.o
	g++ -o bin/dndsh build/main.o build/character.o -lreadline

build/main.o : src/main.cpp
	g++ -c -Wall -Iincludes -o build/main.o src/main.cpp

build/character.o : src/character.cpp
	g++ -c -Wall -Iincludes -o build/character.o src/character.cpp

clean :
	rm -rf build/* bin/*
