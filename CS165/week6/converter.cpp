/*********************************************************************
** Author: Jonathan Nicolosi
** Date: February 2, 2016
** Description: Convert binary to decimal and decimal to binary.
*********************************************************************/

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

/*********************************************************************
** Description: Converts a string which is a binary representation of
** a decimal number to an integer.
*********************************************************************/

int binToDec(string binary, unsigned int i = 0) //pass
{
    int sum = 0;
    if (i < binary.length()) //base case: recursive steps = the length of the string
    {
        if (binary[i] == '1'){
            sum = pow(2, binary.length()-1-i); //raise 2 to the power of the position of the current element in the string.
        }
        return sum + binToDec(binary, ++i);//return sum and increment recursive function to the next step.
    }
    return sum; //return final value
}

/*********************************************************************
** Description: Converts an integer to a string
**
*********************************************************************/
string convertInt(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

/*********************************************************************
** Description: Converts a decimal number to its binary representation.
**
*********************************************************************/

string decToBin(int);
static string binary;
string decToBin(int num)
{
    if(num!=0)
    {
        binary = convertInt(num%2) + binary; //get remainder
        decToBin(num/2);
    }
    return(binary);
}

/* int main()
{

    string s = "0101";

    cout << decToBin(3) << endl;

    cout << binToDec(s);




    return 0;
} */
