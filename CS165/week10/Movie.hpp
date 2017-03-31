/*********************************************************************
** Author: Jonathan Nicolosi
** Date: March 10, 2016
** Description: Movie class declaration
*********************************************************************/

#ifndef MOVIE_HPP
#define MOVIE_HPP
#include "LibraryItem.hpp"
#include <string>

class Movie : public LibraryItem
{
private:
	std::string director;
public:
	static const int CHECK_OUT_LENGTH = 7;
	// function prototypes
	std::string getDirector();
	virtual int getCheckOutLength();
	Movie(std::string id, std::string title, std::string inDirector) : LibraryItem(id, title)		// constructor
	{
		director = inDirector;
	}
};
#endif
