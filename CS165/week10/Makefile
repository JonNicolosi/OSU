all: lib

lib: libMain.o Library.o Album.o Book.o Movie.o Patron.o LibraryItem.o
	g++ -g libMain.o Library.o Album.o Book.o Movie.o Patron.o LibraryItem.o -o lib

libMain.o: libMain.cpp Library.hpp Book.hpp Album.hpp Movie.hpp Patron.hpp LibraryItem.hpp LibraryItem.cpp
	g++ -c libMain.cpp

Library.o: Library.cpp Library.hpp Book.hpp Album.hpp Movie.hpp Patron.hpp LibraryItem.hpp LibraryItem.cpp
	g++ -c Library.cpp

clean:
	rm -f *.o