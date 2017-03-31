#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int main()
{
	//Declare variables
    int sum = 0;
    int number;

	//Create ifstream object
    ifstream input;
    input.open("./input.txt"); //Open file

    if(input.fail()){			//Output error message if file is not found.
        cerr << "Error Opening File" << endl;
        exit(1);
    }

    while(!input.eof()){ //Loop until the end of the file
    input >> number;
    sum = number+sum;
    }

	//Create ofstream object
    ofstream output;
    output.open("output.txt");	//Create output file
    output << sum;

    input.close();	//Close ifstream
    output.close();	//Close ofstream

    return 0;
}
