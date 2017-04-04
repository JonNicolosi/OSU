#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <dirent.h> 
#include <stdbool.h>

void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void randomize ( int arr[], int n )
{
    // Use a different seed value so that we don't get same
    // result each time we run this program
    srand ( time(NULL) );
 
    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
	int i;
    for (i = n-1; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i+1);
 
        // Swap arr[i] with the element at random index
        swap(&arr[i], &arr[j]);
    }
}

void printArray (int arr[], int n)
{
	int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]+1);
    printf("\n");
}

int main() {
		
	char buf[1024];
	int pid = getpid();		
	char intpidtocharpid[50];
		
	sprintf(intpidtocharpid, "%d", pid);
	getcwd(buf, sizeof(buf));
		
		
	strcat(buf, "/nicolosj.rooms.");
		
	strcat(buf, intpidtocharpid);
	/****************************
	
	CREATE DIRECTORY
	
	*****************************/
	struct stat st = {0};
		if (stat(buf, &st) == -1) {
			mkdir(buf, 0755);
		}

	char * roomnames[10];
	roomnames[0] = "Room 1";
	roomnames[1] = "Room 2";
	roomnames[2] = "Room 3";
	roomnames[3] = "Room 4";
	roomnames[4] = "Room 5";
	roomnames[5] = "Room 6";
	roomnames[6] = "Room 7";
	roomnames[7] = "Room 8";
	roomnames[8] = "Room 9";
	roomnames[9] = "Room 10";
	
	//FOR THE PURPOSE OF NAMING THE ROOMS
	int shuffle1[10] = {0,1,2,3,4,5,6,7,8,9};
	int n = sizeof(shuffle1)/ sizeof(shuffle1[0]);
	randomize(shuffle1, 10);

	/****************************
	
	CREATE FILE POINTERS
	
	*****************************/
	
	FILE *fp1;
	FILE *fp2;
	FILE *fp3;
	FILE *fp4;
	FILE *fp5;
	FILE *fp6;
	FILE *fp7;
	
	char filelocation[1024];
	
	strcpy(filelocation, strcat(strcat(buf,"/"),roomnames[shuffle1[0]]));
	strcat(filelocation, ".txt");
		
	fp1 = fopen(filelocation, "w");
	fprintf(fp1, "ROOM NAME: ");
	fprintf(fp1, roomnames[shuffle1[0]]);
	fprintf(fp1,"\n");
	fclose(fp1);
	
	int shuffle2[7];
	int b;
	for(b = 0; b < 7; b++){
		shuffle2[b] = shuffle1[b];
	}
	
	randomize(shuffle2, 7);
	
	int a;
	int counter = 0;
	srand (time(NULL));
	int numofconnections = rand() % 5 + 4;
	for(a = 1; a < numofconnections+1; a++){
		if(shuffle2[a-1]!=shuffle1[0]){
			fp1 = fopen(filelocation, "a");
			fprintf(fp1,"CONNECTION ");
			fprintf(fp1,"%i",a-counter);
			fprintf(fp1,": ");
			fprintf(fp1, roomnames[shuffle2[a-1]]);
			fprintf(fp1,"\n");
			fclose(fp1);
		}
		else{
			counter++;
		}
	}
	
	/****************************
	
	Check to make sure we can get to the next room by checking to see if the room has been printed already.
	If it hasn't, print it.
	
	*****************************/
	
	int wayfoward1 = 0;
	
	for(b = 0; b < numofconnections; b++){
		if(shuffle2[b]==shuffle1[1])
			wayfoward1++;
	}
	if(wayfoward1==0){
		fp1 = fopen(filelocation, "a");
		fprintf(fp1,"CONNECTION ");
		fprintf(fp1,"%i", numofconnections-counter+1);
		fprintf(fp1,": ");
		fprintf(fp1,"%s", roomnames[shuffle1[1]]);
		fprintf(fp1,"\n");
		fclose(fp1);
	}
	
	
	fp1 = fopen(filelocation, "a");
	fprintf(fp1,"ROOM TYPE: START_ROOM");
	fclose(fp1);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	char buf2[1024];
	int pid2 = getpid();		
	char intpidtocharpid2[50];
		
	sprintf(intpidtocharpid2, "%d", pid);
	getcwd(buf2, sizeof(buf2));
		
	strcat(buf2, "/nicolosj.rooms.");
		
	strcat(buf2, intpidtocharpid2);
	
	char filelocation2[1024];
	
	strcpy(filelocation2, strcat(strcat(buf2,"/"),roomnames[shuffle1[1]]));
	strcat(filelocation2, ".txt");
	
	fp2 = fopen(filelocation2, "w");
	fprintf(fp2, "ROOM NAME: ");
	fprintf(fp2, roomnames[shuffle1[1]]);
	fprintf(fp2,"\n");
	fclose(fp2);
	
	int shuffle3[7];

	for(b = 0; b < 7; b++){
		shuffle3[b] = shuffle2[b];
	}
	
	randomize(shuffle3, 7);
	
	int a2;
	int counter2 = 0;
	int prevcounter2 = 0;
	srand (time(NULL));
	int numofconnections2 = rand() % 4 + 3;
	for(a2 = 1; a2 < numofconnections2+1; a2++){
		if(shuffle3[a2-1]==shuffle1[0])
			prevcounter2++;
		if(shuffle3[a2-1]!=shuffle1[1] && counter2<2){
			fp2 = fopen(filelocation2, "a");
			fprintf(fp2,"CONNECTION ");
			fprintf(fp2,"%i",a2-counter2);
			fprintf(fp2,": ");
			fprintf(fp2, roomnames[shuffle3[a2-1]]);
			fprintf(fp2,"\n");
			fclose(fp2);
		}
		else{
			counter2++;
		}
	}
	
	int wayfoward2 = 0;
	fp2 = fopen(filelocation2, "a");
	if(prevcounter2==0){
		fprintf(fp2,"CONNECTION ");
		fprintf(fp2,"%i", numofconnections2-counter2+1);
		fprintf(fp2,": ");
		fprintf(fp2,"%s", roomnames[shuffle1[0]]);
		fprintf(fp2,"\n");
	}
	fclose(fp2);
	
	for(b = 0; b < numofconnections2; b++){
		if(shuffle3[b]==shuffle1[2])
			wayfoward2++;
	}
	
		if(wayfoward2==0){
			fp2 = fopen(filelocation2, "a");
			fprintf(fp2,"CONNECTION ");
			fprintf(fp2,"%i", numofconnections2-counter2+2-prevcounter2);
			fprintf(fp2,": ");
			fprintf(fp2,"%s", roomnames[shuffle1[2]]);
			fprintf(fp2,"\n");
			fclose(fp2);
		}
	fp2 = fopen(filelocation2, "a");
	fprintf(fp2,"ROOM TYPE: MID_ROOM");
	fclose(fp2);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	char buf3[1024];
	int pid3 = getpid();		
	char intpidtocharpid3[50];
		
	sprintf(intpidtocharpid3, "%d", pid);
	getcwd(buf3, sizeof(buf3));
		
	strcat(buf3, "/nicolosj.rooms.");
		
	strcat(buf3, intpidtocharpid3);
	
	char filelocation3[1024];
	
	strcpy(filelocation3, strcat(strcat(buf3,"/"),roomnames[shuffle1[2]]));
	strcat(filelocation3, ".txt");
	
	fp3 = fopen(filelocation3, "w");
	fprintf(fp3, "ROOM NAME: ");
	fprintf(fp3, roomnames[shuffle1[2]]);
	fprintf(fp3,"\n");
	fclose(fp3);
	
	int shuffle4[7];

	for(b = 0; b < 7; b++){
		shuffle4[b] = shuffle3[b];
	}
	
	randomize(shuffle4, 7);
	
	int a3;
	int counter3 = 0;
	int prevcounter3 = 0;
	srand (time(NULL));
	int numofconnections3 = rand() % 4 + 3;
	for(a3 = 1; a3 < numofconnections3+1; a3++){
		if(shuffle4[a3-1]==shuffle1[1])
			prevcounter3++;
		if(shuffle4[a3-1]!=shuffle1[2] && counter3 < 2){
			fp3 = fopen(filelocation3, "a");
			fprintf(fp3,"CONNECTION ");
			fprintf(fp3,"%i",a3-counter3);
			fprintf(fp3,": ");
			fprintf(fp3, roomnames[shuffle4[a3-1]]);
			fprintf(fp3,"\n");
			fclose(fp3);
		}
		else{
			counter3++;
		}
	}
	
	fp3 = fopen(filelocation3, "a");
	if(prevcounter3==0){
	fprintf(fp3,"CONNECTION ");
	fprintf(fp3,"%i", numofconnections3-counter3+1);
	fprintf(fp3,": ");
	fprintf(fp3,"%s", roomnames[shuffle1[1]]);
	fprintf(fp3,"\n");
	}
	int wayfoward3 = 0;
	fclose(fp3);
	
	for(b = 0; b < numofconnections3; b++){
		if(shuffle4[b]==shuffle1[3])
			wayfoward3++;
	}
	
	if(wayfoward3==0){
		fp3 = fopen(filelocation3, "a");
		fprintf(fp3,"CONNECTION ");
		fprintf(fp3,"%i", numofconnections3-counter3+2-prevcounter3);
		fprintf(fp3,": ");
		fprintf(fp3,"%s", roomnames[shuffle1[3]]);
		fprintf(fp3,"\n");
		fclose(fp3);
	}
	
	fp3 = fopen(filelocation3, "a");
	fprintf(fp3,"ROOM TYPE: MID_ROOM");
	fclose(fp3);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	char buf4[1024];
	int pid4 = getpid();		
	char intpidtocharpid4[50];
		
	sprintf(intpidtocharpid4, "%d", pid);
	getcwd(buf4, sizeof(buf4));
		
	strcat(buf4, "/nicolosj.rooms.");
		
	strcat(buf4, intpidtocharpid4);
	
	char filelocation4[1024];
	
	strcpy(filelocation4, strcat(strcat(buf4,"/"),roomnames[shuffle1[3]]));
	strcat(filelocation4, ".txt");
	
	fp4 = fopen(filelocation4, "w");
	fprintf(fp4, "ROOM NAME: ");
	fprintf(fp4, roomnames[shuffle1[3]]);
	fprintf(fp4,"\n");
	fclose(fp4);
	
	int shuffle5[7];

	for(b = 0; b < 7; b++){
		shuffle5[b] = shuffle4[b];
	}
	
	randomize(shuffle5, 7);
	
	int a4;
	int counter4 = 0;
	int prevcounter4 = 0;
	srand (time(NULL));
	int numofconnections4 = rand() % 4 + 3;
	for(a4 = 1; a4 < numofconnections4+1; a4++){
		if(shuffle5[a4-1]==shuffle1[2])
			prevcounter4++;
		if(shuffle5[a4-1]!=shuffle1[3] && counter4 < 2){
			fp4 = fopen(filelocation4, "a");
			fprintf(fp4,"CONNECTION ");
			fprintf(fp4,"%i",a4-counter4);
			fprintf(fp4,": ");
			fprintf(fp4, roomnames[shuffle5[a4-1]]);
			fprintf(fp4,"\n");
			fclose(fp4);
		}
		else{
			counter4++;
		}
	}
	
	fp4 = fopen(filelocation4, "a");
	if(prevcounter4==0){
	fprintf(fp4,"CONNECTION ");
	fprintf(fp4,"%i", numofconnections4-counter4+1);
	fprintf(fp4,": ");
	fprintf(fp4,"%s", roomnames[shuffle1[2]]);
	fprintf(fp4,"\n");
	}
	fclose(fp4);
	int wayfoward4 = 0;
	
	for(b = 0; b < numofconnections4; b++){
		if(shuffle5[b]==shuffle1[4])
			wayfoward4++;
	}
	
	if(wayfoward4==0){
		fp4 = fopen(filelocation4, "a");
		fprintf(fp4,"CONNECTION ");
		fprintf(fp4,"%i", numofconnections4-counter4+2-prevcounter4);
		fprintf(fp4,": ");
		fprintf(fp4,"%s", roomnames[shuffle1[4]]);
		fprintf(fp4,"\n");
		fclose(fp4);
	}
	
	fp4 = fopen(filelocation4, "a");
	fprintf(fp4,"ROOM TYPE: MID_ROOM");
	fclose(fp4);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	char buf5[1024];
	int pid5 = getpid();		
	char intpidtocharpid5[50];
		
	sprintf(intpidtocharpid5, "%d", pid);
	getcwd(buf5, sizeof(buf5));
		
	strcat(buf5, "/nicolosj.rooms.");
		
	strcat(buf5, intpidtocharpid5);
	
	char filelocation5[1024];
	
	strcpy(filelocation5, strcat(strcat(buf5,"/"),roomnames[shuffle1[4]]));
	strcat(filelocation5, ".txt");
	
	fp5 = fopen(filelocation5, "w");
	fprintf(fp5, "ROOM NAME: ");
	fprintf(fp5, roomnames[shuffle1[4]]);
	fprintf(fp5,"\n");
	fclose(fp5);
	
	int shuffle6[7];

	for(b = 0; b < 7; b++){
		shuffle6[b] = shuffle5[b];
	}
	
	randomize(shuffle6, 7);
	
	int a5;
	int counter5 = 0;
	int prevcounter5 = 0;
	srand (time(NULL));
	int numofconnections5 = rand() % 4 + 3;
	for(a5 = 1; a5 < numofconnections5+1; a5++){
		if(shuffle6[a5-1]==shuffle1[3])
			prevcounter5++;
		if(shuffle6[a5-1]!=shuffle1[4] && counter5 < 2){
			fp5 = fopen(filelocation5, "a");
			fprintf(fp5,"CONNECTION ");
			fprintf(fp5,"%i",a5-counter5);
			fprintf(fp5,": ");
			fprintf(fp5, roomnames[shuffle6[a5-1]]);
			fprintf(fp5,"\n");
			fclose(fp5);
		}
		else{
			counter5++;
		}
	}
	
	fp5 = fopen(filelocation5, "a");
	if(prevcounter5==0){
	fprintf(fp5,"CONNECTION ");
	fprintf(fp5,"%i", numofconnections5-counter5+1);
	fprintf(fp5,": ");
	fprintf(fp5,"%s", roomnames[shuffle1[3]]);
	fprintf(fp5,"\n");
	}
	fclose(fp5);
	int wayfoward5 = 0;
	
	for(b = 0; b < numofconnections5; b++){
		if(shuffle6[b]==shuffle1[5])
			wayfoward5++;
	}
	
	if(wayfoward5==0){
		fp5 = fopen(filelocation5, "a");
		fprintf(fp5,"CONNECTION ");
		fprintf(fp5,"%i", numofconnections5-counter5+2-prevcounter5);
		fprintf(fp5,": ");
		fprintf(fp5,"%s", roomnames[shuffle1[5]]);
		fprintf(fp5,"\n");
		fclose(fp5);
	}
	fp5 = fopen(filelocation5, "a");
	fprintf(fp5,"ROOM TYPE: MID_ROOM");
	fclose(fp5);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	char buf6[1024];
	int pid6 = getpid();		
	char intpidtocharpid6[50];
		
	sprintf(intpidtocharpid6, "%d", pid);
	getcwd(buf6, sizeof(buf6));
		
	strcat(buf6, "/nicolosj.rooms.");
		
	strcat(buf6, intpidtocharpid6);
	
	char filelocation6[1024];
	
	strcpy(filelocation6, strcat(strcat(buf6,"/"),roomnames[shuffle1[5]]));
	strcat(filelocation6, ".txt");
	
	fp6 = fopen(filelocation6, "w");
	fprintf(fp6, "ROOM NAME: ");
	fprintf(fp6, roomnames[shuffle1[5]]);
	fprintf(fp6,"\n");
	fclose(fp6);
	
	int shuffle7[7];

	for(b = 0; b < 7; b++){
		shuffle7[b] = shuffle6[b];
	}
	
	randomize(shuffle7, 7);
	
	int a6;
	int counter6 = 0;
	int prevcounter6 = 0;
	srand (time(NULL));
	int numofconnections6 = rand() % 4 + 3;
	for(a6 = 1; a6 < numofconnections6+1; a6++){
		if(shuffle7[a6-1]==shuffle1[4])
			prevcounter6++;
		if(shuffle7[a6-1]!=shuffle1[5] && counter6 < 2){
			fp6 = fopen(filelocation6, "a");
			fprintf(fp6,"CONNECTION ");
			fprintf(fp6,"%i",a6-counter6);
			fprintf(fp6,": ");
			fprintf(fp6, roomnames[shuffle7[a6-1]]);
			fprintf(fp6,"\n");
			fclose(fp6);
		}
		else{
			counter6++;
		}
	}
	
	fp6 = fopen(filelocation6, "a");
	if(prevcounter6==0){
	fprintf(fp6,"CONNECTION ");
	fprintf(fp6,"%i", numofconnections6-counter6+1);
	fprintf(fp6,": ");
	fprintf(fp6,"%s", roomnames[shuffle1[4]]);
	fprintf(fp6,"\n");
	}
	fclose(fp6);
	int wayfoward6 = 0;
	
	for(b = 0; b < numofconnections6; b++){
		if(shuffle7[b]==shuffle1[6])
			wayfoward6++;
	}
	
	if(wayfoward6==0){
		fp6 = fopen(filelocation6, "a");
		fprintf(fp6,"CONNECTION ");
		fprintf(fp6,"%i", numofconnections6-counter6+2-prevcounter6);
		fprintf(fp6,": ");
		fprintf(fp6,"%s", roomnames[shuffle1[6]]);
		fprintf(fp6,"\n");
		fclose(fp6);
	}
	fp6 = fopen(filelocation6, "a");
	fprintf(fp6,"ROOM TYPE: MID_ROOM");
	fclose(fp6);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	char buf7[1024];
	int pid7 = getpid();		
	char intpidtocharpid7[50];
		
	sprintf(intpidtocharpid7, "%d", pid);
	getcwd(buf7, sizeof(buf7));
		
	strcat(buf7, "/nicolosj.rooms.");
		
	strcat(buf7, intpidtocharpid7);
	
	char filelocation7[1024];
	
	strcpy(filelocation7, strcat(strcat(buf7,"/"),roomnames[shuffle1[6]]));
	strcat(filelocation7, ".txt");
	
	fp7 = fopen(filelocation7, "w");
	fprintf(fp7, "ROOM NAME: ");
	fprintf(fp7, roomnames[shuffle1[6]]);
	fprintf(fp7,"\n");
	fclose(fp7);
	
	int shuffle8[7];

	for(b = 0; b < 7; b++){
		shuffle8[b] = shuffle7[b];
	}
	
	randomize(shuffle8, 7);
	
	int a7;
	int counter7 = 0;
	int prevcounter7 = 0;
	srand (time(NULL));
	int numofconnections7 = rand() % 4 + 3;
	for(a7 = 1; a7 < numofconnections7+1; a7++){
		if(shuffle8[a7-1]==shuffle1[5])
			prevcounter7++;
		if(shuffle8[a7-1]!=shuffle1[6] && counter7 < 2){
			fp7 = fopen(filelocation7, "a");
			fprintf(fp7,"CONNECTION ");
			fprintf(fp7,"%i",a7-counter7);
			fprintf(fp7,": ");
			fprintf(fp7, roomnames[shuffle8[a7-1]]);
			fprintf(fp7,"\n");
			fclose(fp7);
		}
		else{
			counter7++;
		}
	}
	
	fp7 = fopen(filelocation7, "a");
	if(prevcounter7==0){
	fprintf(fp7,"CONNECTION ");
	fprintf(fp7,"%i", numofconnections7-counter7+1);
	fprintf(fp7,": ");
	fprintf(fp7,"%s", roomnames[shuffle1[5]]);
	fprintf(fp7,"\n");
	}
	fclose(fp7);

	fp7 = fopen(filelocation7, "a");
	fprintf(fp7,"ROOM TYPE: END_ROOM");
	fclose(fp7);
	
	char * 	paths[1000];
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	/****************************
	
	FILL THE ARRAY THAT CONTAINS THE CONNECTIONS TO THE OTHER ROOMS.
	
	*****************************/
	
	int connectionarray[7][8];
	int j;
	int k;
 
	for(j=1;j<numofconnections+1; j++){
		connectionarray[0][0] = shuffle1[0]+1;
		if(shuffle1[0]+1!=shuffle2[j-1]+1)
			connectionarray[0][j] = shuffle2[j-1]+1;
	} 
	for(j=1;j<numofconnections2+1; j++){
		connectionarray[1][0] = shuffle1[1]+1;
		if(shuffle1[1]+1!=shuffle3[j-1]+1)
			connectionarray[1][j] = shuffle3[j-1]+1;
	} 
	for(j=1;j<numofconnections3+1; j++){
		connectionarray[2][0] = shuffle1[2]+1;
		if(shuffle1[2]+1!=shuffle4[j-1]+1)
		connectionarray[2][j] = shuffle4[j-1]+1;
	} 
	for(j=1;j<numofconnections4+1; j++){
		connectionarray[3][0] = shuffle1[3]+1;
		if(shuffle1[3]+1!=shuffle5[j-1]+1)
		connectionarray[3][j] = shuffle5[j-1]+1;
	} 
	for(j=1;j<numofconnections5+1; j++){
		connectionarray[4][0] = shuffle1[4]+1;
		if(shuffle1[4]+1!=shuffle6[j-1]+1)
		connectionarray[4][j] = shuffle6[j-1]+1;
	} 
	for(j=1;j<numofconnections6+1; j++){
		connectionarray[5][0] = shuffle1[5]+1;
		if(shuffle1[5]+1!=shuffle7[j-1]+1)
		connectionarray[5][j] = shuffle7[j-1]+1;
	} 
	for(j=1;j<numofconnections7+1; j++){
		connectionarray[6][0] = shuffle1[6]+1;
		if(shuffle1[6]+1!=shuffle8[j-1]+1)
		connectionarray[6][j] = shuffle8[j-1]+1;
	} 
	
	/****************************
	
	MAKE SURE WE CAN GET BACK.
	
	*****************************/
	
	if(prevcounter2==0)
	connectionarray[1][7] = shuffle1[0]+1;
	if(prevcounter3==0)
	connectionarray[2][7] = shuffle1[1]+1;
	if(prevcounter4==0)
	connectionarray[3][7] = shuffle1[2]+1;
	if(prevcounter5==0)
	connectionarray[4][7] = shuffle1[3]+1;
	if(prevcounter6==0)
	connectionarray[5][7] = shuffle1[4]+1;
	if(prevcounter7==0)
	connectionarray[6][7] = shuffle1[5]+1;

	/****************************
	
	MAKE SURE WE CAN GO FOWARD.
	
	*****************************/

	int x;
	int instances = 0;
	if(wayfoward1==0){
		for(x = 0; x < 7; x++){
			if(connectionarray[0][x]==0 && instances<1){
				connectionarray[0][x] = shuffle1[1]+1;
				instances++;
			}
		}
	}
	instances = 0;
	if(wayfoward2==0){
		for(x = 0; x < 7; x++){
			if(connectionarray[1][x]==0 && instances<1){
				connectionarray[1][x] = shuffle1[2]+1;
				instances++;
			}
		}
	}
	instances = 0;
	if(wayfoward3==0){
		for(x = 0; x < 7; x++){
			if(connectionarray[2][x]==0 && instances<1){
				connectionarray[2][x] = shuffle1[3]+1;
				instances++;
			}
		}
	}
	instances = 0;
	if(wayfoward4==0){
		for(x = 0; x < 7; x++){
			if(connectionarray[3][x]==0 && instances<1){
				connectionarray[3][x] = shuffle1[4]+1;
				instances++;
			}
		}
	}
	instances = 0;
	if(wayfoward5==0){
		for(x = 0; x < 7; x++){
			if(connectionarray[4][x]==0 && instances<1){
				connectionarray[4][x] = shuffle1[5]+1;
				instances++;
			}
		}
	}
	instances = 0;
	if(wayfoward6==0){
		for(x = 0; x < 7; x++){
			if(connectionarray[5][x]==0 && instances<1){
				connectionarray[5][x] = shuffle1[6]+1;
				instances++;
			}
		}
	}
	
	int count = 0;	
	char userInput[1024];
	
	printf("%s", "CURRENT LOCATION: ");
	printf("%s", roomnames[shuffle1[0]]);
	printf("%s", "\nPOSSIBLE CONNECTIONS: ");
	int d;
	int e;
	int misses = 0;
	int index = 0;
	
	paths[0] = roomnames[shuffle1[0]];
	count++;
	
	for(d = 1; d < 8; d++){

		if(connectionarray[0][d]!=0){
			printf("%s", roomnames[connectionarray[0][d]-1]);	
			if(connectionarray[0][d+1]==0 && connectionarray[0][d+2]==0 && d < 7)
				break;
			if(d==6 && connectionarray[0][7]==0)
				break;
			if(connectionarray[0][d]!=0 && d < 7)
				printf("%s", ", ");
		}
	}
	printf("%s", ".\nWHERE TO? >");
	
	fgets(userInput, 1024, stdin);
	bool valid = false;
	
	/****************************
	
	CHECK TO MAKE SURE ROOM IS VALID.
	
	*****************************/
	
	while(valid==false){
		
		for(e = 0; e < 7; e++){
			if(strcmp(userInput, roomnames[shuffle2[e]])!=10)
				misses++;
			if(strcmp(userInput, roomnames[shuffle2[e]])==10){
				if(userInput[5]-48 == 1 && userInput[6]-48 ==0){
					index = 10;
				}
				else{
					index = userInput[5]-48;
				}
			}
		}
			if(misses==7){
				valid = false;
				misses=0;
				printf("%s", "\nHUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
				printf("%s", "\nCURRENT LOCATION: ");
				printf("%s", roomnames[shuffle1[0]]);
				printf("%s", "\nPOSSIBLE CONNECTIONS: ");
				for(d = 1; d < 8; d++){
					if(connectionarray[0][d]!=0){
						printf("%s", roomnames[connectionarray[0][d]-1]);	
					if(connectionarray[0][d]!=0 && d < 7)
						printf("%s", ", ");
					}
				}
				printf("%s", ".\nWHERE TO? >");
				fgets(userInput, 1024, stdin);

			}
			else{
				valid = true;
				misses = 0;
			}
	}
	misses = 0;
	int m;
	int p;
	int q;
	int u;
	int currentLocation = index;
	int nonzero = 0;
	
	paths[1] = roomnames[currentLocation-1];
	count++;
	
	/****************************
	
	KEEP LOOPING UNTIL THE PLAYER GUESSES THE LAST ROOM.
	
	*****************************/
	
	while(strcmp(userInput, roomnames[shuffle1[6]])!=10){
		
		printf("%s", "\nCURRENT LOCATION: ");
		printf("%s", roomnames[currentLocation-1]);
		printf("%s", "\nPOSSIBLE CONNECTIONS: ");
		for(m = 0; m < 7; m++){
			if(connectionarray[m][0]==currentLocation){
				for(p = 1; p < 8; p++){
					if(connectionarray[m][p]!=0){
						printf("%s", roomnames[connectionarray[m][p]-1]);	
					if(connectionarray[m][p+1]==0 && connectionarray[m][p+2]==0 && p < 7)
						break;
					if(p==6 && connectionarray[m][7]==0)
						break;
					if(connectionarray[m][p]!=0 && p < 7)
						printf("%s", ", ");
					}	
				}
			}
		}
		
		printf("%s", ".\nWHERE TO? >");	
		fgets(userInput, 1024, stdin);
		
		valid = false;
		
		while(valid == false){
			
			for(m = 0; m < 7; m++){
				if(connectionarray[m][0]==currentLocation){
					for(p = 1; p < 8; p++){
						if(connectionarray[m][p]==0)
							nonzero++;
						if(connectionarray[m][p]!=0){
							if(strcmp(userInput, roomnames[connectionarray[m][p]-1])!=10){
								misses++;
								
							}
							if(strcmp(userInput, roomnames[connectionarray[m][p]-1])==10){
								if(userInput[5]-48 == 1 && userInput[6]-48 ==0){
									index = 10;
								}		
								else{
									index = userInput[5]-48;
								}
							}
						}
					}
				}	
			}
		misses = misses+nonzero;

		if(misses==7){
		
		valid = false;
		misses=0;
		printf("%s", "\nHUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
		printf("%s", "\nCURRENT LOCATION: Room ");
		printf("%i", currentLocation);
		printf("%s", "\nPOSSIBLE CONNECTIONS: ");
		for(m = 0; m < 7; m++){
			if(connectionarray[m][0]==currentLocation){
				for(p = 1; p < 8; p++){
					if(connectionarray[m][p]!=0){
						printf("%s", roomnames[connectionarray[m][p]-1]);	
					if(connectionarray[m][p+1]==0 && connectionarray[m][p+2]==0 && p < 7)
						break;
					if(p==6 && connectionarray[m][7]==0)
						break;
					if(connectionarray[m][p]!=0 && p < 7)
						printf("%s", ", ");
					}	
				}
			}
		}
				printf("%s", ".\nWHERE TO? >");
				fgets(userInput, 1024, stdin);

		}
		else{
			valid = true;
			misses = 0;
			currentLocation = index;
			nonzero = 0;
			}
					misses = 0;
		nonzero = 0;
		}

		currentLocation = index;
		misses = 0;
		nonzero = 0;
		
		paths[count] = roomnames[currentLocation-1];
		count++;
		
		
	}

	/****************************
	
	PRINT THE COUNT AND THE STEPS.
	
	*****************************/
	
	int z;
	printf("%s", "YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
	printf("%s", "YOU TOOK ");
	printf("%i", count);
	printf("%s", " STEPS\n");
	printf("%s", "YOUR PATH TO VICTORY WAS:\n");
	for(z = 0; z<1000; z++){
		if(paths[z]!=0){
		printf("%s", paths[z]);
		printf("%s", "\n");
		}
	}
	
	
	
	
	
	return 0;
}
