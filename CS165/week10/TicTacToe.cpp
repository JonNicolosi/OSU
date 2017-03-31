/*********************************************************************
** Author: Jonathan Nicolosi
** Date: March 10, 2016
** Description: TicTacToe class implementation
*********************************************************************/

#include "TicTacToe.hpp"
/*********************************************************************
** Description: Play function that continues to loop until a winner is
** decided or there is a draw.
*********************************************************************/
void TicTacToe::play(){

    while(board.gameState()!=2 && board.gameState()==3 && board.gameState()!=0 && board.gameState()!=1){//while the the game is still in progress...
        int x, y;
        cout << "Ok " << this->player << ", give the X and Y coordinates of your move. " << endl << endl;
        cout << "X: ";
        cin >> x;
        cout << endl;
        cout << "Y: ";
        cin >> y;
        cout << endl;
        while(board.makeMove(x,y,player)==false){
            cout << "Square occupied. Please choose another square. ";
            cout << endl;
            cout << "Y: ";
            cin >> y;
            cout << endl;
        }
        board.makeMove(x,y,player);
        board.print();
        cout << endl;
        if(this->player == 'x'){
            this->player = 'o';
        }
        else if(this->player == 'o'){
            this->player = 'x';
        }
    }
    cout << endl;
    if(board.gameState()==0){
        cout << "X Wins.";
    }
    else if(board.gameState()==1){
        cout << "Y Wins.";
    }
    else if(board.gameState()==2){
        cout << "Draw.";
    }
}

int main()
{
    char player;
    cout << "Which player should go first? " << endl;
    cin >> player;
    Board b;
    TicTacToe t(b, player);
    t.play();
    return 0;
}

