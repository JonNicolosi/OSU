/* CS261- Assignment 1 - Q.5*/
/* Name: Jonathan Nicolosi
 * Date: 04/10/2016
 * Solution description: Make every other letter a different case.
 */

#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/
     int i;
     for(i = 0; i<100; i++){
        if(word[i]=='\0'){
            return;
        }
        if(i % 2){
            if (word[i] >= 'A' && word[i] <= 'Z')
            word[i] = toLowerCase(word[i]);
        }
        else{
            if (word[i] >= 'a' && word[i] <= 'z')
            word[i] = toUpperCase(word[i]);
        }
     }
}

int main(){
    /*Read word from the keyboard using scanf*/
    printf("Please enter a string: ");
    char buffer[100];
    scanf("%s", buffer);
    /*Call sticky*/
    sticky(buffer);
    /*Print the new word*/
    printf("%s\n", buffer);
    return 0;
}
