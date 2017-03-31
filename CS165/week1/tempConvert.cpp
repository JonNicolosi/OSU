#include <iostream>

using namespace std;

int main()
{
   double celsius;

   cout << "Please enter a Celsius temperature." << endl;

   cin >> celsius;

   cout << "The equivalent Fahrenheit temperature is: " << endl << (celsius*1.8)+32;

}
