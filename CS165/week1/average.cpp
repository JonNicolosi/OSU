#include <iostream>

using namespace std;

int main()
{
    double numbers[5];
    int increment = 0;
    double sum = 0;
    double average;


    cout << "Please enter five numbers. " << endl;

    while (increment<5){
        cin >> numbers[increment];
        increment++;
    }

    for(int i = 0; i<5; i++){
        sum = sum+numbers[i];
    }

    average = sum/5;

    cout << "The average of those numbers is: " << endl;
    cout << average;

    return 0;
}
