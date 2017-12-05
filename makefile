all:build myexe doc doczip

build:main.o game.o othello.o
	g++ -o build main.o game.o othello.o

myexe:main.o game.o othello.o
	g++ -o myexe main.o game.o othello.o

main.o:main.cc game.h othello.h
	g++ -c main.cc

game.o:game.cc game.h
	g++ -c game.cc

othello.o:othello.cc othello.h
	g++ -c othello.cc

doczip:
	zip -r termproject.zip ~/3560/termproject/termproject

clean:
	rm -f build main.o game.o othello.o myexe termproject.zip -r html latex

doc:
	doxygen ./main.cc game.cc othello.cc
