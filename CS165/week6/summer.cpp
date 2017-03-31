/*********************************************************************
** Author: Jonathan Nicolosi
** Date: February 10, 2016
** Description: Sum values of an array recursively.
*********************************************************************/

#include <iostream>

using namespace std;

/*********************************************************************
** Description: Recursive function that takes as parameters an array
** of doubles and the size of the array as an integer. It returns the
** sum of the values in the array.
*********************************************************************/

double summer(double arr[], int sizeofarr)
{
  if (sizeofarr==0)  // base case
    return 0;   // no recursive call
  else
    {
      int small = summer(arr, sizeofarr - 1); // solve smaller problem
      // use solution of smaller to solve larger
      return small + arr[sizeofarr - 1] ;
    }
}

/* int main()
{

    double x[4] = {1,2,3,4};

    cout << summer(x, 4);


    return 0;
} */
