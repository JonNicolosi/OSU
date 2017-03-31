#include <iostream>

using namespace std;

int main()
{
    int amount;

    int Q;
    int D;
    int N;
    int P;

    cout << "Please enter an amount in cents less than a dollar. ";

    cin >> amount;

    Q = amount/25;
    amount = amount%25;
    D = amount/10;
    amount = amount%10;
    N = amount/5;
    amount = amount%5;
    P = amount;

    cout << "Q: " << Q << endl;
    cout << "D: " << D << endl;
    cout << "N: " << N << endl;
    cout << "P: " << P << endl;


    return 0;
}
