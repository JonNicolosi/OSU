/*********************************************************************
** Author: Jonathan Nicolosi
** Date: March 10, 2016
** Description: Board class implementation
*********************************************************************/

#include "Board.hpp"

using namespace std;
/*********************************************************************
** Description: Constructor that initializes the board's square to 0.
**
*********************************************************************/
Board::Board(){
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            moves[i][j] = '0';
        }

    }
}
/*********************************************************************
** Description: Prints the board.
**
*********************************************************************/
void Board::print(){
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            cout << moves[i][j];
        }
        cout << endl;
    }

}
/*********************************************************************
** Description: Records moves on the board. If move is illegal, return
** false.
*********************************************************************/
bool Board::makeMove(int x, int y, char s){
    if(moves[x][y]=='0'){
        moves[x][y] = s;
        return true;
    }
    else{
        return false;
    }
}
/*********************************************************************
** Description: Has an if statement for each possible win combination.
** Either returns a winner, game in progress, or draw.
*********************************************************************/
int Board::gameState(){

    if(moves[0][0]=='x' && moves[0][1]=='x' && moves[0][2]=='x'){
        return XWIN;
    }
    else if(moves[0][0]=='x' && moves[1][0]=='x' && moves[2][0]=='x'){
        return XWIN;
    }
    else if(moves[2][0]=='x' && moves[2][1]=='x' && moves[2][2]=='x'){
        return XWIN;
    }
    else if(moves[0][2]=='x' && moves[1][2]=='x' && moves[2][2]=='x'){
        return XWIN;
    }
    else if(moves[0][1]=='x' && moves[1][1]=='x' && moves[2][1]=='x'){
        return XWIN;
    }
    else if(moves[1][0]=='x' && moves[1][1]=='x' && moves[1][2]=='x'){
        return XWIN;
    }
    else if(moves[0][0]=='x' && moves[1][1]=='x' && moves[2][2]=='x'){
        return XWIN;
    }
    else if(moves[2][0]=='x' && moves[1][1]=='x' && moves[0][2]=='x'){
        return XWIN;
    }
    else if(moves[0][0]=='o' && moves[0][1]=='o' && moves[0][2]=='o'){
        return OWIN;
    }
    else if(moves[0][0]=='o' && moves[1][0]=='o' && moves[2][0]=='o'){
        return OWIN;
    }
    else if(moves[2][0]=='o' && moves[2][1]=='o' && moves[2][2]=='o'){
        return OWIN;
    }
    else if(moves[0][2]=='o' && moves[1][2]=='o' && moves[2][2]=='o'){
        return OWIN;
    }
    else if(moves[0][1]=='o' && moves[1][1]=='o' && moves[2][1]=='o'){
        return OWIN;
    }
    else if(moves[1][0]=='o' && moves[1][1]=='o' && moves[1][2]=='o'){
        return OWIN;
    }
    else if(moves[0][0]=='o' && moves[1][1]=='o' && moves[2][2]=='o'){
        return OWIN;
    }
    else if(moves[2][0]=='o' && moves[1][1]=='o' && moves[0][2]=='o'){
        return OWIN;
    }

        for(int i = 0; i<3; i++){
            for(int j = 0; j<3; j++){
                if(moves[i][j]=='0'){
                    return INPROGRESS;
                }
            }
        }

    return DRAW;

}
