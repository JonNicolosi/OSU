#include <iostream>

using namespace std;


    void smallSort(int&a, int&b, int&c){ //Variables passed to function by reference.

    int temp;
    if(a > b) //If a is greater than b, swap a and b.
    {
        temp = a;
        a = b;
        b = temp;
    }

    if(b > c)	//If b is greater than c, swap b and c.
    {
        temp = b;
        b = c;
        c = temp;
    }

    if(a > b)	//If after swapping b and c, a is now greater than b, swap a and b again.
    {
        temp = a;
        a = b;
        b = temp;
    }

    }


// int main()
// {
    // int a = 14;
    // int b = -90;
    // int c = 2;
    // smallSort(a, b, c);
    // cout << a << ", " << b << ", " << c << endl;
    // return 0;
// }
