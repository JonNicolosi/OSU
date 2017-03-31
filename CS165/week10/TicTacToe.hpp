/*********************************************************************
** Author: Jonathan Nicolosi
** Date: March 10, 2016
** Description: TicTacToe class declaration. Derived from Board class
*********************************************************************/

#ifndef TICTACTOE_HPP_INCLUDED
#define TICTACTOE_HPP_INCLUDED
#include "Board.hpp"

class TicTacToe : public Board{

private:
    Board board;//board object from base class.
    char player;
public:
    TicTacToe(Board b, char p) : Board(){//constructor
        board = b;
        player = p;

    }
    void play();
};

#endif // TICTACTOE_HPP_INCLUDED
