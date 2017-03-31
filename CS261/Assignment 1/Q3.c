/* CS261- Assignment 1 - Q.3*/
/* Name: Jonathan Nicolosi
 * Date: 04/10/2016
 * Solution description: Sort an array of random numbers between 0 and 100.
 */

#include <stdio.h>

void sort(int* number, int n){
     /*Sort the given array number , of length n*/
   int *i, *j, swap;
    int *end = NULL;

    if(n < 2 || number == NULL)
        return;

    end = number + n - 1;

    for(i = number; i < end; i++)
    {
        for(j = i + 1; j <= end; j++)
        {
            if(*j < *i)
            {
                swap = *i;
                *i = *j;
                *j = swap;
            }
        }
    }
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    /*Allocate memory for an array of n integers using malloc.*/
    int* intArray = malloc(sizeof(int) * n);
    /*Fill this array with random numbers, using rand().*/
    int i;
    for(i = 0; i < n; i++){
        intArray[i] = rand() % 100;
    }
    /*Print the contents of the array.*/
    int j;
    for(j = 0; j < n; j++){
        printf("%d ", intArray[j]);
    printf("\n");
    }
    printf("\n");
    /*Pass this array along with n to the sort() function of part a.*/
    sort(intArray, n);
    /*Print the contents of the array.*/
    int k;
    for(k = 0; k < n; k++){
        printf("%d ", intArray[k]);
    printf("\n");
    }

    free(intArray);

    return 0;
}
