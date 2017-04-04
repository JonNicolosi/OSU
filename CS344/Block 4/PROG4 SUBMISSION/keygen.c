/*
keygen.c
Jon Nicolosi
CS344
Generates a key file
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CHARACTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ "

char genRandUpper(void) {
	return CHARACTERS[rand() % 27];
}

char *genKey(int numOfChars) {
	char *key = malloc(sizeof(char) * (numOfChars + 2));
	int index;

	for (index = 0; index < numOfChars; index++) {
		key[index] = genRandUpper();
	}

	key[numOfChars] = '\n';

	return key;
}

int main(int argc, char *argv[]) {
	srand(time(NULL));

	if (argc < 2) {
		printf("Usage: keygen keylength\n");
		exit(1);
	}
	char *key = genKey(atoi(argv[1]));
	printf("%s", key);

	return 0;
}