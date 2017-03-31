/* CS261- Assignment 1 - Q. 0*/
/* Name: Jonathan Nicolosi
 * Date: 04/10/2016
 * Solution description: Print out addresses pointed to by pointers
 */

#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
    printf("%i\n",*iptr);
     /*Print the address pointed to by iptr*/
    printf("%p\n",(void*)iptr);
     /*Print the address of iptr itself*/
    printf("%p\n",(void*)&iptr);
}

int main(){

    /*declare an integer x*/

    int x = 5;

    /*print the address of x*/

    printf("%p\n",(void*)&x);

    /*Call fooA() with the address of x*/
    fooA(&x);


    /*print the value of x*/
    printf("%i\n",x);

    return 0;
}
