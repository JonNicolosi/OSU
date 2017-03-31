#include <iostream>

using namespace std;


    int hailstone(int x){
        int counter = 0;
        while(x!=1){
            if(x%2==0){	//If x mod 2 == 0, then the number divided by 2 has no remainder. Therefore, it must be even.
                x = x/2;
            }
            else if(x%2==1){	//If x mod 2 == 1, then the number divided by 2 has a remainder of 1. Therefore, it must be odd.
                x = (x*3)+1;
            }
            counter++; //Increment counter.

        }
        return counter; //Return counter value.
    }


// int main()
// {
    // int x;
    // cin >> x;
    // cout << hailstone(x);

    // return 0;
// }
