all: assembling linking clean

assembling:
	clang++ -Wall -Werror -c geometry.cpp

linking: geometry.o
	clang++ geometry.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

clean: 
	rm -rf *.o
