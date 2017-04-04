/*
** 
Jonathan Nicolosi
CS372

Chat client that will allow the user to send messages to a server.

Source: http://www.cs.columbia.edu/~danr/courses/6761/Fall00/hw/pa1/6761-sockhelp.pdf


*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
// the port client will be connecting to
#define MAXDATASIZE 512 // max number of bytes we can get at once
int main(int argc, char *argv[])
{


	
	int socket_fd, numbytes;
	char buf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in their_addr; // connector’s address information
	
	if (argc !=3) {
		fprintf(stderr,"usage: client hostname\n");
		exit(1);
	}
	if ((he=gethostbyname(argv[1])) == NULL) { // get the host info
		perror("gethostbyname");
		exit(1);
	}
	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	

	
	their_addr.sin_family = AF_INET; // host byte order
	
	their_addr.sin_port = htons(atoi(argv[2])); // short, network byte order
	
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	
	bzero(&(their_addr.sin_zero), 8); // zero the rest of the struct
	
	if (connect(socket_fd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}
	if ((numbytes=recv(socket_fd, buf, MAXDATASIZE-1, 0)) == -1) {
		perror("recv");
		exit(1);
	}
	
	buf[numbytes] = '\0';
	printf(buf);
	
	int sentusername = 0;
	
	while(1) {
		
		if(sentusername == 0){
			
			printf("%s", "Enter username: ");
			fgets(buf, MAXDATASIZE-1, stdin);
			
		}
		if(sentusername==1){
			fgets(buf,MAXDATASIZE-1,stdin);
		}
        if ((send(socket_fd,buf, strlen(buf),0))== -1) {
                fprintf(stderr, "Failure Sending Message\n");
                close(socket_fd);
                exit(1);
        }
        else {
                
                numbytes = recv(socket_fd, buf, sizeof(buf),0);
                if ( numbytes <= 0 )
                {
                        printf("Connection closed.\n");
                        //Break from the While
                        break;
                }

                buf[numbytes-1] = '\0';
                printf(buf);
           }
		   sentusername = 1;
		   
    }
    close(socket_fd);
	
	

	return 0;
}



