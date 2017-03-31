/* #include <iostream>
#include "ShoppingCart.hpp"
#include "Item.hpp"
using namespace std;

int main()
{
    Item a("affidavit", 179.99, 12);
    Item b("Bildungsroman", 0.7, 20);
    Item c("capybara", 4.5, 6);
    Item d("dirigible", 0.05, 16);

    ShoppingCart sc1;
    sc1.addItem(&a);
    sc1.addItem(&b);
    sc1.addItem(&c);
    sc1.addItem(&d);

    double diff = sc1.totalPrice();
    cout << diff << endl << endl;


    return 0;
}
 */