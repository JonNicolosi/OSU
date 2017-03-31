/*********************************************************************
** Author: Jonathan Nicolosi
** Date: March 2, 2016
** Description: Postfix expression evaluator
*********************************************************************/

#include<iostream>
#include<stack>
#include<string>

using namespace std;

/*********************************************************************
** Description:Function to evaluate Postfix expression and return output
**
*********************************************************************/

double postfixEval(string expression)
{
	// Declaring a Stack from Standard template library in C++.
	stack<double> S;

	for(int i = 0;i< expression.length();i++) {

		// Scanning each character from left.
		// If character is a delimitter, move on.
		if(expression[i] == ' ' || expression[i] == ',') continue;

		// If character is operator, pop two elements from stack, perform operation and push the result back.
		else if(expression[i]=='+'|| expression[i]=='-'||expression[i]=='*'||expression[i]=='/') {
			// Pop two operands.
			double operand2 = S.top(); S.pop();
			double operand1 = S.top(); S.pop();
			// Perform operation
			double result;

			if(expression[i]=='+'){
                result = operand1 + operand2;
			}
			else if(expression[i]=='-'){
                result = operand1-operand2;
			}
			else if(expression[i]=='*'){
                result = operand1*operand2;
			}
			else if(expression[i]=='/'){
                result = operand1/operand2;
			}

			//Push back result of operation on stack.
			S.push(result);
		}
		else if(expression[i]>='0'&& expression[i]<='9'){
			// Extract the numeric operand from the string
			// Keep incrementing i as long as you are getting a numeric digit.
			double operand = 0;
			while(i<expression.length() && expression[i]>='0'&& expression[i]<='9') {
				// For a number with more than one digits, as we are scanning from left to right.
				// Everytime , we get a digit towards right, we can multiply current total in operand by 10
				// and add the new digit.
				operand = (operand*10) + (expression[i] - '0');
				i++;
			}
			// Finally, you will come out of while loop with i set to a non-numeric character or end of string
			i--;

			// Push operand on stack.
			S.push(operand);
		}
	}
	// If expression is in correct format, Stack will finally have one element. This will be the output.
	return S.top();
}

int main()
{
	// string expression;
	// cout<<"Enter Postfix Expression \n";
	// getline(cin,expression);
	// double result = postfixEval(expression);
	// cout<<"Output = "<<result<<"\n";
}




