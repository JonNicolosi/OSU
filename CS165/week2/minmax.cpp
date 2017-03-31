/*********************************************************************
** Author: Jonathan Nicolosi
** Date: January 13th, 2016
** Description: Program designed to return the minimum and maximum numbers in a sequence of numbers.
*********************************************************************/

#include <iostream>

using namespace std;

int main()
{
	//Declare variables
    int quantity;
    int counter = 0;
    int number;
    int maximum;
    int minimum;


    cout << "How many integers would you like to enter? " << endl;

    cin >> quantity;
	//Output grammatically correct sentence which asks the user how many numbers he/she would like to input.
    if(quantity==1){
        cout << "Please enter " << quantity << " integer. " << endl;
    }
    else{
    cout << "Please enter " << quantity << " integers. " << endl;
    }

	//Loop until all numbers have been entered by user.
    while(counter<quantity){
        cin >> number;
        if(quantity==1){ //Immediately output the entered number if there is only one number.
            cout << "Min: " << number << endl;
            cout << "Max: " << number << endl;
        }
		//Set the minimum and maximum to the first number entered.
        if(counter==0){
        maximum = number;
        minimum = number;
        }
		
        if(counter>0){
            if(number>maximum){
                maximum = number; //If the number being entered is greater than the current max, make that the new max.
            }
            if(number<minimum){	//If the number being entered is less than the current min, make that the new min.
                minimum = number;
            }
        }
		//Count loops
        counter++;

    }

    if(quantity!=1){

    cout << "Min: " << minimum << endl;
    cout << "Max: " << maximum << endl;
    }
    return 0;
}
