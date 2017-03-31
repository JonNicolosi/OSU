#include <iostream>

using namespace std;

int main()
{
	//Declare variables
    int number;
    int toguess;
    int counter = 0;

    cout << "Enter a number for the player to guess: " << endl;

    cin >> toguess;

    cout << "Enter your guess: " << endl;



    while(number!=toguess){	//Loop until correct number is guessed
        cin >> number;
        if(number<toguess){
            cout << "Too low - try again. ";
        }
        if(number>toguess){
            cout << "Too high - try again. ";
        }
        cout << endl;
        counter++;//Count how many times the loop has completed.
    }

    if(counter==1){
        cout << "You guessed it in " << counter << " try.";
    }
    else{
    cout << "You guessed it in " << counter << " tries.";
    }
    return 0;
}
