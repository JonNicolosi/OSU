/*
otp_dec_d.c
Jon Nicolosi
CS344
Daemon that is used for decoding text that is sent to it.
*/
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h>

#define MAXCHARS 200000
#define CHARACTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ "
#define MAXQUEUE 5

char *decodeString(char *string, char *key, int string_length);
int getCharOrd(char character);

void processConnection(int sockFD) {
	int clientSockFD,
		PID,
		cipherLen,
		keyLen;
	struct sockaddr_in client;
	socklen_t clilen = sizeof(client);
	char ciphertext[MAXCHARS],
		 key[MAXCHARS];
	char *plaintext;

	while (1) {

		if ((clientSockFD = accept(sockFD, (struct sockaddr *) &client, &clilen)) < 0) {
			fprintf(stderr, "ERROR:  otp_dec_d is not able to accept any connections\n");
			continue;
		}

		PID = fork();
		if (PID == 0) {
			memset(ciphertext, 0, MAXCHARS);
			memset(key, 0, MAXCHARS);


			if ((cipherLen = read(clientSockFD, ciphertext, MAXCHARS)) < 0) {
				fprintf(stderr, "ERROR:  otp_dec_d is unable to read plain text file\n");
			}

			if (write(clientSockFD, "I got your message", 18) < 0) {
				fprintf(stderr, "ERROR:  otp_dec_d cannot send an acknowledgement!\n");
			}

			if ((keyLen = read(clientSockFD, key, MAXCHARS)) < 0) {
				fprintf(stderr, "ERROR:  otp_dec_d cannot read the key file\n");
			}

			plaintext = decodeString(ciphertext, key, cipherLen);

			if (write(clientSockFD, plaintext, cipherLen) < 0) {
				fprintf(stderr, "ERROR:  otp_dec_d cannot send the acknowledgement\n");
			}
		}
	}

	close(clientSockFD);
}

void BindSockToPort(struct sockaddr_in *server, int sockFD, int portNum) {
	if (bind(sockFD, (struct sockaddr *) server, sizeof(*server)) < 0) {
		fprintf(stderr, "ERROR:  otp_dec_d unable to bind socket to port %d\n", portNum);
		exit(1);
	}
}

void createServer(struct sockaddr_in *server, int portNum) {
	memset(server, '\0', sizeof(server));
	server->sin_family = AF_INET;
	server->sin_addr.s_addr = INADDR_ANY;
	server->sin_port = htons(portNum);
}

char decodeChar(char character, char key) {
	char difference = getCharOrd(character) - getCharOrd(key);
	char decodedChar = (((difference % 27) + 27) % 27);
	return decodedChar;
}

char *decodeString(char *string, char *key, int string_length) {
	char *decodedString = malloc(sizeof(char) * (string_length));
	int index;

	for (index = 0; index < string_length - 1; index++) {
		decodedString[index] = CHARACTERS[decodeChar(string[index], key[index])];
	}

	return decodedString;
}

int getCharOrd(char character) {
	if (character == ' ') {
		return 26;
	}
	return character - 'A';
}

int main(int argc, char *argv[]) {
	int sockFD,
		portNum;
	socklen_t clilen;
	struct sockaddr_in server;

	if (argc < 2) {
		printf("Usage: otp_enc_d listening_port\n");
		exit(1);
	}
	
	portNum = atoi(argv[1]);
	if (portNum <= 0 || portNum >= 65535) {
		printf("otp_enc_d: invalid port\n");
		exit(1);
	}

	if ((sockFD = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "ERROR:  otp_dec_d could not create socket on port %d\n", portNum);
		exit(1);
	}
	
	createServer(&server, portNum);
	BindSockToPort(&server, sockFD, portNum);
	if (listen(sockFD, MAXQUEUE) == -1) {
		fprintf(stderr, "ERROR:  otp_dec_d cannot use port %d\n", portNum);
		exit(1);
	}
	processConnection(sockFD);
	close(sockFD);

	return 0;
}