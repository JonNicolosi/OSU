/*
otp_enc_d.c
Jon Nicolosi
CS344
Daemon that is used for encoding text that is sent to it. 
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

char *encodeString(char *string, char *key, int string_length);
int getCharOrd(char character);

void processConnections(int sockFD) {
	int clientSockFD,
		PID,
		plaintextLen,
		keyLen;
	struct sockaddr_in client;
	socklen_t clilen = sizeof(client);
	char plaintext[MAXCHARS],
		 key[MAXCHARS];
	char *ciphertext;

	while (1) {

		if ((clientSockFD = accept(sockFD, (struct sockaddr *) &client, &clilen)) < 0) {
			fprintf(stderr, "ERROR:  otp_enc_d is unable to accept any connections\n");
			continue;
		}

		PID = fork();
		if (PID == 0) {
			memset(plaintext, 0, MAXCHARS);
			memset(key, 0, MAXCHARS);

			if ((plaintextLen = read(clientSockFD, plaintext, MAXCHARS)) < 0) {
				fprintf(stderr, "ERROR:  otp_enc_d is not able to read the plain text file\n");
			}

			if (write(clientSockFD, "I got your message", 18) < 0) {
				fprintf(stderr, "ERROR:  otop_enc_d cannot send acknowledgement\n");
			}

			if ((keyLen = read(clientSockFD, key, MAXCHARS)) < 0) {
				fprintf(stderr, "ERROR:  otp_enc_d cannot read key file\n");
			}

			ciphertext = encodeString(plaintext, key, plaintextLen);

			if (write(clientSockFD, ciphertext, plaintextLen) < 0) {
				fprintf(stderr, "ERROR:  otp_enc_d cannot send any acknowledgement!\n");
			}
		}
	}

	close(clientSockFD);
}

void BindSocketToPort(struct sockaddr_in *server, int sockFD, int portNum) {
	if (bind(sockFD, (struct sockaddr *) server, sizeof(*server)) < 0) {
		fprintf(stderr, "ERROR:  otp_enc_d is not able to bind the socket to port %d\n", portNum);
		exit(1);
	}
}

void createServer(struct sockaddr_in *server, int portNum) {
	memset(server, '\0', sizeof(server));
	server->sin_family = AF_INET;
	server->sin_addr.s_addr = INADDR_ANY;
	server->sin_port = htons(portNum);
}

char encodeChar(char character, char key) {
	char sum = getCharOrd(character) + getCharOrd(key);
	char encoded_character = (((sum % 27) + 27) % 27);
	return encoded_character;
}


char *encodeString(char *string, char *key, int string_length) {
	char *encodedString = malloc(sizeof(char) * (string_length));
	int index;

	for (index = 0; index < string_length - 1; index++) {
		encodedString[index] = CHARACTERS[encodeChar(string[index], key[index])];
	}

	return encodedString;
}

int getCharOrd(char character) {
	if (character == ' ') {
		return 26;
	}
	return character - 'A';
}

void ListenForConnections(int sockFD, int portNum) {
	if (listen(sockFD, MAXQUEUE) == -1) {
		fprintf(stderr, "ERROR:  otp_enc_d cannot use port %d\n", portNum);
		exit(1);
	}
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
		fprintf(stderr, "ERROR:  otp_enc_d could not create a new socket\n");
		exit(1);
	}
	createServer(&server, portNum);
	BindSocketToPort(&server, sockFD, portNum);
	ListenForConnections(sockFD, portNum);
	processConnections(sockFD);
	close(sockFD);

	return 0;
}