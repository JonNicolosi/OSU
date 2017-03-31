/*********************************************************************
** Author: Jonathan Nicolosi
** Date: March 10, 2016
** Description: Board class declaration
*********************************************************************/
#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED
#include <iostream>
#include <string>

using namespace std;

enum state {XWIN, OWIN, DRAW, INPROGRESS};

class Board{

private:
    char moves[3][3]; //declare character array
public:
    Board();//default constructor
    Board(char m[3][3]);
    bool makeMove(int, int, char);//records the player's move on the board.
    void print();//print function
    int gameState();//returns the state of the game

};

#endif // BOARD_HPP_INCLUDED
