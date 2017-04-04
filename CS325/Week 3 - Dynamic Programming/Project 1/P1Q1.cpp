#include <iostream>
using namespace std;

void MAXSUBARRAY(int arr[]){

    int currentMax = 0;

    int sum = 0;

    for(int i = 0; i<10; i++){

        sum = 0;

            for(int j = i; j<10; j++){

                    sum = arr[j] + sum;
                    if(sum>currentMax){
                        currentMax = sum;
                    }
            }
    }
    cout << currentMax;

}

int main()
{
    int arr[10] = {31, -41, 59, 26, -53, 58, 97, -93, -23, 84};

    MAXSUBARRAY(arr);

}
