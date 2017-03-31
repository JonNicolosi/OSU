/*********************************************************************
** Author: Jonathan Nicolosi
** Date: January 27th, 2016
** Description: A program designed to find the mode in an array.
*********************************************************************/

#include <iostream>
#include <vector>
#include <string>
using namespace std;


    void findMode(int arr[], int arraysize){

        vector<int> vec; //declare vector

        int mode;

        //Sorting algorithm to sort array
        for(int x=0; x<arraysize; x++){
            for(int y=0; y<arraysize-1; y++){
                if(arr[y]>arr[y+1]){
                        int temp = arr[y+1];
                        arr[y+1] = arr[y];
                        arr[y] = temp;

			}
		}
	}
        //Algorithm to find mode
        int counter = 1;
        int m = 0;
        mode = arr[0];
        for (int pass = 0; pass < arraysize - 1; pass++)
        {
           if ( arr[pass] == arr[pass+1] )
           {
              counter++;
              if ( counter > m )
              {
                  m = counter;
                  mode = arr[pass];
              }
           } else
              counter = 1; // reset counter.
        }

    int counter2 = 0;

    //Determine how many times the mode appears in the array
    for(int b = 0; b<arraysize; b++){
        if(arr[b]==mode){
            counter2++;
        }
    }


    int counter3 = 0;
    //Nested for loops designed to iterate through entire array, counting each element, how many times that element appears in the array, and then comparing that counter to the mode counter.
    for(int j = 0; j<arraysize; j++){
        counter3 = 0;
        for(int k = 0; k<arraysize; k++){
            if(arr[k]==arr[j]){
                counter3++;
                if(counter3==counter2)
                {
                    vec.push_back(arr[j]);
                }
            }
        }
    }
    //Print elements of vector
    for (int i=0; i<vec.size(); i++)
        cout << vec.at(i) << endl;
}


/* int main()
{

   int arr[10] = {1,2,3,4,5,6,7,8,9,10};

    findMode(arr, 10);


    return 0;
} */
