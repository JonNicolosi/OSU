/* CS261- Assignment 1 - Q.4*/
/* Name: Jonathan Nicolosi
 * Date: 04/10/2016
 * Solution description: Generate random IDs and scores for students. Then sort them.
 */

#include <stdio.h>
#include <stdlib.h>

struct student{
	int id;
	int score;
};

void generate(struct student* students, int n){
    /*Generate random ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
    int i;
    for(i = 0; i < n; i++)
    {
        students[i].id = i + 1;
        students[i].score = rand() % 101;
    }

}

void output(struct student* students, int n){
    /*Output information about the ten students in the format:
             ID1 Score1
             ID2 score2
             ID3 score3
             ...
             ID10 score10*/
    int i;
    for(i = 0; i < n; i++)
    {
        printf("%d %d\n", students[i].id, students[i].score);
    }

    printf("\n");
}

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/
    int *i, *j, swap;
    int *end = NULL;

    if(n < 2 || students == NULL)
        return;

    end = students + n - 1;

    for(i = students; i < end; i++)
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
    /*Declare an integer n and assign it a value.*/
    int n = 10;
    /*Allocate memory for n students using malloc.*/
    struct student* students = malloc(sizeof(struct student) * n);
    /*Generate random IDs and scores for the n students, using rand().*/
    generate(students, n);
    /*Print the contents of the array of n students.*/
    output(students, n);
    /*Pass this array along with n to the sort() function*/
    sort(students, n);
    /*Print the contents of the array of n students.*/
    output(students, n);

    free(students);

    return 0;
}
