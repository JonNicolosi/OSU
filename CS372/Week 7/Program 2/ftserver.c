/*********************************************************************************
 * Author: Jonathan Nicolosi
 * Date: 11/29/2016
 * Class: CS372
 * Project 2
 *
 * File Transfer Server
 *
 * Usage: ftserver <port number>
 *
 *********************************************************************************/

#include <signal.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdint.h>

//For small files
#define BUFFER 1024

//For large files
#define MAXBUFFER 8192

int quit(char *buffer, char *handle);
int sendMessage(int sockfd, char *msg);
unsigned receiveCheck(int sockfd);
int InitializeConnection(int port);
void sigintHandle(int sigNum);
int getInput(char *buffer, char *handle);
int max(int a, int b);
void RMNL(char *string);
int checkPort(char *input);
int sendResponse(char *outgoing, char *message, int clientSocket);
int openFile(char *fileName, char *string);
int sendFile(char* file, int ClientDataSocket, int clientSocket);
unsigned sendCheck(int sockfd, unsigned num);
int handleRequest(int clientSocket, char *buffer);
int receiveMessage(int, char*, unsigned);

int main(int argc, char *argv[]){
    signal(SIGCHLD, sigintHandle); //Initialize signal handler

    char buffer[BUFFER];        //Message buffer
    char incoming[BUFFER];       //Incoming message buffer
    char outgoing[BUFFER];	//Outgoing message buffer
    int size;                   //Message size
    int r;                      //Send/Receive status
    int dataport;		//Data connection port

    //Verify proper command line usage
    if(argc != 2){
        fprintf(stderr, "\nusage:\n $ ftserver [port number]\n\n");
        exit(0);
    }

    //Check that the port is valid
    int port = checkPort(argv[1]);
    if(port < 0){
        fprintf(stderr, "Port Invalid.\n");
        exit(1);
    }

    //Create socket, then bind to port and listen on port.
    int sockfd = InitializeConnection(port);
    if(sockfd < 0){
        fprintf(stderr, "Error: Could not listen on Port %d", port);
        exit(1);
    }
    printf("Listening on Port %d\n", port);

    int pid, status;		//For child processes

    //Continuously listen for connections
    while(1){
        int clientSocket = accept(sockfd, NULL, NULL);

        //Connection failed
        if(clientSocket < 0){
            fprintf(stderr, "Error: Failed Accepting Connection\n");
            close(clientSocket);

        //Connection success
        } else {
            //New fork
            pid = fork();

            //Forking fail
            if(pid < 0){
                printf("Fork Failed. Exiting. ");
                exit(1);
            }

            //This is a child process
            else if(pid == 0){
                printf("Client Has Connected; Starting Session\n");

                int requestNum = handleRequest(clientSocket, incoming);
                printf("Request # is: %d\n", requestNum);

                dataport = receiveCheck(clientSocket);		//Data connection port

                //Message is good
                if(r == 0){
                    //Create new socket, bind and listen for data
                    int ClientDataFD = InitializeConnection(dataport);
                    printf("Opening Data Connection on Port %d\n", dataport);

                    //Listen
                    int ClientDataSocket = accept(ClientDataFD, NULL, NULL);

                    //If client sends (-l) command
                    if(requestNum == 1){
                        char directory[BUFFER];

                        //Get full directory path
                        getcwd(buffer, BUFFER);


                        // http://www.thegeekstuff.com/2012/06/c-directory/
                        /*************************************************************************************************************************************************/
                        //Get file list
                        DIR *dir = NULL;
                        dir = opendir(buffer);
                        struct dirent *dirstruct = NULL;
                        while((dirstruct = readdir(dir)) != NULL){
                            
                            if((strncmp(dirstruct->d_name, ".", strlen(dirstruct->d_name)) != 0) && (strncmp(dirstruct->d_name, "..", strlen(dirstruct->d_name)) != 0)){
                                strncat(directory, "[", 1);
                                strncat(directory, dirstruct->d_name, strlen(dirstruct->d_name));
                                strncat(directory, "] ", 2);
                            }
                        }
                        /*************************************************************************************************************************************************/
						
                        //Send response on control connection to receive data on data connection
                        sendResponse(outgoing, "DATA", clientSocket);
                        //Send list of files
                        sendResponse(outgoing, directory, ClientDataSocket);
                        close(clientSocket);
                        _exit(0);

                    //Get command (-g)
                    } else if (requestNum == 2){
                        //Put filename into message
                        size = receiveCheck(clientSocket);
                        r = receiveMessage(clientSocket, incoming, size);
                        incoming[size] = '\0';               //Append terminating character
                        printf("Client Has Requested [%s]\n", incoming);

                        //Make sure file exists
                        //Get full directory path
                        getcwd(buffer, BUFFER);

                        //Get list of files
                        DIR *dir = NULL;
                        dir = opendir(buffer);
                        struct dirent *dirstruct = NULL;
                        int fileExists = 0;
                        while((dirstruct = readdir(dir)) != NULL){
                            //Make sure file exists
                            if(strncmp(incoming, dirstruct->d_name, max(strlen(dirstruct->d_name), strlen(incoming))) == 0){
                                fileExists = 1;	//File is valid
                            }
                        }

                        //File is valid
                        if(fileExists == 1){
                            printf("[%s] is a valid filename\n", incoming);
                            //Read file into buffer
                            char filebuffer[MAXBUFFER];
                            openFile(incoming, filebuffer);

                            //Send response on control connection to receive data on data connection
                            sendResponse(outgoing, "DATA", clientSocket);

                            //Send file on data connection
                            sendFile(filebuffer, ClientDataSocket, clientSocket);
                            printf("Transfer Complete\n");
                            close(clientSocket); 
                            _exit(0);

                        //File is not valid
                        } else {
                            printf("[%s] does not exist.\n", incoming);
                            //Send error message on control connection
                            sendResponse(outgoing, "Filename invalid.", clientSocket);
                            close(clientSocket);
                            _exit(0);
                        }
                    
                    //Command invalid. Exit.
                    } else {
                        sendResponse(outgoing, "Invalid Command.", clientSocket);
                        close(clientSocket);
                        _exit(0);
                    }


                //Message incomplete. Exit
                } else {
                    fprintf(stderr, "Message Receiving Error. \n");
                    close(clientSocket);
                    _exit(0);
                }

            //Parent
            } else {

            }
        }
    }
    
    return 0;
}

//Return value determines the type of request
int handleRequest(int clientSocket, char *buffer){
    int size = receiveCheck(clientSocket);   
    int r = receiveMessage(clientSocket, buffer, size);     
    buffer[size] = '\0';


    if(strncmp("-g", buffer, strlen(buffer)) == 0){
        return 2;
    } else if(strncmp("-l", buffer, strlen(buffer)) == 0) {
        return 1;
    } else {
        return -1;
    }
}


int max(int a, int b){
    if(a >= b){
        return a;
    }
    else return b;
}


int openFile(char *fileName, char *string){

// http://stackoverflow.com/questions/14002954/c-programming-how-to-read-the-whole-file-contents-into-a-buffer
/*************************************************************************************************************/
        // open the file
        FILE *fileptr;
        fileptr = fopen(fileName, "rb");
        fseek(fileptr, 0, SEEK_END);
        long fsize = ftell(fileptr);
        fseek(fileptr, 0, SEEK_SET);

        char *buffer = malloc(fsize + 1);
        fread(buffer, fsize, 1, fileptr);
        buffer[fsize] = '\0';	
        
        fclose(fileptr);
        strncpy(string, buffer, MAXBUFFER);
        return 0;
/*************************************************************************************************************/
}


//Send file to client
int sendFile(char* file, int ClientDataSocket, int clientSocket){
    int r = sendCheck(ClientDataSocket, (strlen(file)));    
    r = sendMessage(ClientDataSocket, file);            
    printf("File Sent: Closing Data Connection to Client\n");
    close(ClientDataSocket);           
}



//Sends message in buffer to client
int sendResponse(char *outgoing, char* message, int clientSocket){
    strncpy(outgoing, message, BUFFER);			
    int r = sendCheck(clientSocket, (strlen(outgoing)));	
    r = sendMessage(clientSocket, outgoing);		
}


void sigintHandle(int sigNum){
    pid_t pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);
}

int getInput(char *buffer, char *handle){
    printf("%s$ ", handle);
    fgets(buffer, (BUFFER -1), stdin);
    RMNL(buffer);
    return 0;
}

int quit(char *buffer, char *handle){
    getInput(buffer, handle);
    if(strncmp(buffer, "\\quit", 5) == 0){
        printf("Exiting chat application\n");
        return 1;
    }
    else return 0;
}

int receiveMessage(int socketFD, char *output, unsigned size){
	char buffer[BUFFER];
	unsigned r;
	unsigned total = 0;

	while(total < size){
		r = read(socketFD, buffer+total, size-total);
		total += r;

		if(r < 0){
			return -1;
		}

		else if(r == 0){
			total = size - total;
		}
	}

	strncpy(output, buffer, size);

	return 0;
}

int sendMessage(int sockfd, char *msg){

	unsigned r;


	unsigned size = strlen(msg)+1;


	unsigned total = 0;

	//Loop until entire file is sent
	while(total < size) {
		//Start where message left off
		r = write(sockfd, msg+total, size-total);


		total += r;

		//If error
		if(r < 0){
			return -1;
		}

		//Done
		else if(r == 0){
			total = size - total;
		}
	}

	return 0;
}

unsigned sendCheck(int sockfd, unsigned num){
	unsigned realnum = num;
	int r = write(sockfd, &realnum, sizeof(unsigned));
	if(r < 0){
		return -1;
	}
	else return 0;
}

unsigned receiveCheck(int sockfd){
	unsigned num;
	int r = read(sockfd, &num, sizeof(unsigned));
	if(r < 0){
		return -1;
	}
	else return num;
}

int InitializeConnection(int port){
	int sockfd;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		return -1;
	}
	

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;

// http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html#setsockoptman
/*******************************************************************************/
        int optval = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
/*******************************************************************************/


	if(bind(sockfd, (struct sockaddr *) &server, sizeof(server)) < 0){
		return -1;
	}


	if(listen(sockfd, 10) < 0){
		return -1;
	}


	return sockfd;
} 

void RMNL(char *string){

        int last = strlen(string) - 1;
        if(string[last] == '\n') {
                string[last] = '\0';
        }
}

int checkPort(char *input){
	int port = atoi(input);
	if(port < 1024 || port > 65535){
		return -1;
	}
	return port;
}