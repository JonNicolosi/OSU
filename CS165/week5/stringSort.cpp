/*********************************************************************
** Author: Jonathan Nicolosi
** Date: 2/3/2016
** Description: Sort string lexicogrphically using selection sort
*********************************************************************/

#include <iostream>
#include <string>


using namespace std;


bool compare(string x, string y){//function for comparing two string lexicogrphically
    for(int a = 0; a<x.length(); a++){//first convert strings to uppercase
        x[a] = toupper(x[a]);
    }
    for(int b = 0; b<y.length(); b++){
        y[b] = toupper(y[b]);
    }

    if(x.compare(y)<0){ //If string x is lexicogrphically less than string y, return true
        return true;
    }
    else{
        return false;
    }

}

void stringSort(string arr[], int n) {

    int startScan, minIndex;
    string minValue;

    for(startScan = 0; startScan < (n-1); startScan++){
        minIndex = startScan;
        minValue = arr[startScan];
        for(int index = startScan+1; index < n; index++){
            if (compare(arr[index], minValue)==true){
                minValue = arr[index];
                minIndex = index;

            }
        }
        arr[minIndex] = arr[startScan];
        arr[startScan] = minValue;
    }

      for(int k = 0; k<n; k++){
        cout << arr[k] << endl;
      }

}


//int main()
//{
//    string arr[10] = {"Jon", "Bob", "Tim", "diana", "brEtt", "Mytt", "Keith", "Tom", "Mike", "Ryan"};
//
//    stringSort(arr, 10);
//
//    return 0;
//}
