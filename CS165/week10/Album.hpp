/*********************************************************************
** Author: Jonathan Nicolosi
** Date: March 10, 2016
** Description: Album class declaration
*********************************************************************/

#ifndef ALBUM_HPP
#define ALBUM_HPP
#include "LibraryItem.hpp"
#include <string>

class Album : public LibraryItem
{
private:
	std::string artist;
public:
	static const int CHECK_OUT_LENGTH = 14;
	// function prototypes
	std::string getArtist();
	virtual int getCheckOutLength();
	Album(std::string id, std::string title, std::string inArtist) : LibraryItem(id, title)		// constructor
	{
		artist = inArtist;
	}
};
#endif
