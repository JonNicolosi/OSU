/*********************************************************************
** Author: Jonathan Nicolosi
** Date: 2/3/16
** Description: Box sorting function
*********************************************************************/

#include <iostream>
#include "Box.hpp"

using namespace std;

void Box::boxSort(Box arr[], int arraySize){

    Box temp;

    for(int i = 0; i < arraySize-1; i++){//uses bubble sort to sort boxes by volume in descending order
        for(int j=1; j<arraySize;j++){
            if(arr[j-1].getVolume() < arr[j].getVolume()){
                temp = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = temp;
            }
        }
    }

    for(int k = 0; k<arraySize; k++){
        cout << arr[k].getVolume() << endl;
    }

}
