/*
otp_enc.c
Jon Nicolosi
CS344
Sends text to the otp_enc_d daemon for decoding.
*/
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXCHARS 200000

void set_up_server_information(struct sockaddr_in *server_address, struct hostent *server);

int main(int argc, char *argv[]) {
	int plaintextFD,
		plaintextCharCount,
		keyFD,
		keyCharCount,
		portNum;
	char plaintextChars[MAXCHARS],
		 keyChars[MAXCHARS];

	if (argc < 4) {
		printf("Usage: otp_enc plaintext key listening_port\n");
		exit(1);
	}
	portNum = atoi(argv[3]);
	if (portNum <= 0 || portNum >= 65535) {
		printf("otp_enc_d: invalid port\n");
		exit(1);
	}
	
	if ((plaintextFD = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "ERROR:  cannot open file named %s\n", argv[1]);
	}

	plaintextCharCount = read(plaintextFD, plaintextChars, MAXCHARS);
	
	int index;

	for (index = 0; index < plaintextCharCount - 1; index++) {
		if (!((plaintextChars[index] >= 65 && plaintextChars[index] <= 90) || (plaintextChars[index] == 32))) {
			fprintf(stderr, "ERROR:  invalid character found in file %s\n", argv[1]);
			exit(1);
		}
	}
	
	close(plaintextFD);

	if ((keyFD = open(argv[2], O_RDONLY)) < 0) {
		fprintf(stderr, "ERROR:  cannot open file named %s\n", argv[2]);
	}
	
	
	keyCharCount = read(keyFD, keyChars, MAXCHARS);
	
	for (index = 0; index < keyCharCount - 1; index++) {
		if (!((keyChars[index] >= 65 && keyChars[index] <= 90) || (keyChars[index] == 32))) {
			fprintf(stderr, "ERROR:  invalid character found in file %s\n", argv[2]);
			exit(1);
		}
	}

	if (keyCharCount < plaintextCharCount) {
		fprintf(stderr, "ERROR:  key file is too short\n");
		exit(1);
	}
		
	int socket_file_descriptor,
		characters_sent;
	struct sockaddr_in server_address;
	struct hostent *server;
	char acknowledgement[MAXCHARS];
	char ciphertext[MAXCHARS];
	
	/*
		Create a socket, or print an error message.
	*/
	if ((socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "ERROR: could not connect to otp_enc_d on port %d\n", portNum);
	}

	memset(&server_address, '\0', sizeof(server_address));
	if ((server = gethostbyname("localhost")) == NULL) {
		fprintf(stderr, "ERROR:  could not connect to localhost\n");
		exit(1);
	}
	server_address.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &server_address.sin_addr.s_addr, server->h_length);
	server_address.sin_port = htons(portNum);

	/*
		Connect to the server or print an error message.
	*/
	if (connect(socket_file_descriptor, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
		fprintf(stderr, "ERROR:  could not connect to otp_enc_d on port %d\n", portNum);
		exit(1);
	}	

	/*
		Send the plain text to the server, or print an error message.
	*/
	if (write(socket_file_descriptor, plaintextChars, plaintextCharCount) < 0) {
		fprintf(stderr, "ERROR:  could not send plain text content to otp_enc_d on port %d", portNum);
		exit(1);
	}

	/*
		Receive an acknowledgement, or print an error message.
	*/
	if (read(socket_file_descriptor, acknowledgement, MAXCHARS) < 0) {
		fprintf(stderr, "ERROR:  did not receive any acknowledgement from server!\n");
		exit(1);
	}

	/*
		Send the key to the server, or print an error message.
	*/
	if (write(socket_file_descriptor, keyChars, keyCharCount) < 0) {
		fprintf(stderr, "ERROR:  could not send key content to otp_enc_d on port %d\n", portNum);
		exit(1);
	}

	/*
		Receive the ciphertext from the server, or print an error message.
	*/
	if (read(socket_file_descriptor, ciphertext, MAXCHARS) < 0) {
		fprintf(stderr, "ERROR:  did not receive ciphertext content from server.\n");
		exit(1);
	}

	/*
		Print the text to stdout.
	*/
	for (index = 0; index < plaintextCharCount - 1; index++) {
		printf("%c", ciphertext[index]);
	}
	printf("\n");

	return 0;
}