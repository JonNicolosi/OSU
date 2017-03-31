#include <iostream>
#include "Library.hpp"
#include <iostream>
using namespace std;

int main()
{
	Book b1("123", "War and Peace", "Tolstoy");
	Book b2("234", "Moby Dick", "Melville");
	Book b3("345", "Phantom Tollbooth", "Juster");
	Patron p1("abc", "Felicity");
	Patron p2("bcd", "Waldo");
	Library lib;
	lib.addLibraryItem(&b1);
	lib.addLibraryItem(&b2);
	lib.addLibraryItem(&b3);
	lib.addPatron(&p1);
	lib.addPatron(&p2);
	lib.checkOutLibraryItem("bcd", "234");
	for (int i=0; i<7; i++)
	   lib.incrementCurrentDate();
	lib.checkOutLibraryItem("bcd", "123");
	lib.checkOutLibraryItem("abc", "345");
	for (int i=0; i<24; i++)
	   lib.incrementCurrentDate();
	double p1Fine = p1.getFineAmount();
	double p2Fine = p2.getFineAmount();

	lib.returnLibraryItem("123");
	// lib.requestLibraryItem("bcd", "123");
	lib.returnLibraryItem("123");
	lib.checkOutLibraryItem("bcd", "123");

	Movie m1("999", "Terminator", "Robertson");
	lib.addLibraryItem(&m1);

	for (int i=0; i<24; i++)
	   lib.incrementCurrentDate();



	// cout << "*** Library ***" << endl;
	// lib.displayLibrary();
	// cout << "*** Patrons ***" << endl;
	// lib.displayPatrons();
	return 0;
}
