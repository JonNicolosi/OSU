/**********************************************************************
 * Jonathan Nicolosi
 * CS 344
 * Program 3
 * Date: 11/17/16
 *********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

void catchSignal(int sigNum);
void getInput();
void isRunning();

int backgroundProcess;  
int inputRedirect; 
int outputRedirect; 


int backgroundPIDS[64]; 
int backgroundProcessCount; 
char initArgs[512];
int exitCode = 0;

void isRunning(){
   int status;
  
   int i;
	//Set statuses for background processes
   for (i = 0; i < backgroundProcessCount; i++)
   {
      if (waitpid(backgroundPIDS[i], &status, WNOHANG) > 0)
      {
         if (WIFEXITED(status))
         {  
            printf("background pid %d is done: exit value %d\n", backgroundPIDS[i],
             WEXITSTATUS(status));
         }
         if (WIFSIGNALED(status))
         {
            printf("background pid %d is done: terminated by signal %d\n", backgroundPIDS[i],
             WTERMSIG(status));
         }
      }
   }  
}

void getInput()
{
   //Flush stdin and stdout
   fflush(stdout);
   fflush(stdin);
   printf(": ");
   fflush(stdin);


   if (fgets(initArgs, sizeof(initArgs), stdin) != NULL)
   {
      char *pointer;
      pointer = strchr(initArgs, '\n'); 
      *pointer = '\0'; 

      backgroundProcess = 0;

      if ((pointer = strchr(initArgs, '&')) != NULL) 
      {
         *pointer = '\0';  
         backgroundProcess = 1; 
      }
      
      
      if ((pointer = strchr(initArgs, '<')) != NULL) 
      {
         inputRedirect = 1; 
     
      }
    
      if ((pointer = strchr(initArgs, '>')) != NULL) 
      {
         outputRedirect = 1;
        
      }

   }
}

void catchSignal(int sigNum)
{

   printf("terminated by signal %d\n", sigNum);

}


int main(){
	//file descriptor
   int fd;


   //Foreground Signals
   struct sigaction foregroundAction;
   foregroundAction.sa_handler = catchSignal;
   sigfillset(&(foregroundAction.sa_mask));
   sigaction(SIGINT, &foregroundAction, NULL);
   foregroundAction.sa_flags = 0;

   
   //Background Signals
   struct sigaction backgroundAction;
   backgroundAction.sa_handler = catchSignal;
   sigfillset(&(backgroundAction.sa_mask));
   sigaction(SIGINT, &backgroundAction, NULL);
   backgroundAction.sa_flags = 0;


   //Normal Signals
   struct sigaction normalAction, initAction;
   initAction.sa_handler = catchSignal;
   sigfillset(&(initAction.sa_mask));
   sigaction(SIGINT, &initAction, &normalAction);
   initAction.sa_flags = 0;


   int status = 0;
   bool exited = true; //Loop while true
   while (exited == true)
   {
      
      //Initialize signals
      sigaction(SIGINT, &initAction, &normalAction);
      sigaction(SIGINT, &backgroundAction, NULL);
      sigaction(SIGINT, &foregroundAction, NULL);

      isRunning(); //Determine what processes are running in the background
      getInput(); //Get input from stdin

      if (strncmp(initArgs, "#", 1) == 0){ 
		  continue; 
	  }

      if (strcmp(initArgs, "exit") == 0)
      {
         exited = false; 
      }
      else if (strcmp(initArgs, "status") == 0)
      {

         status = WEXITSTATUS(status);
         printf("exit value %d\n", status);
         
      }
      else if (strncmp("cd", initArgs, 2) == 0)
      {
         //Store current working directory in a buffer.
         char cwd[1024];
         getcwd(cwd, sizeof(cwd));
       
         //Parse out desired directory
         char src[32];
         strcpy(src, initArgs);
         int length = strlen(src);
         
         if (length > 2)
         {
            length - 3; 
            char dest[32]; 
            int i = 0;

            for (i = 0; i < length; i++) 
            {
               dest[i] = src[i+3];
            }
  
            strcpy(src, dest); 
            strcat(cwd, "/"); 
            strcat(cwd, src); 
         
            chdir(cwd);
			int b;
			for(b = 0; b < 32; b++){
				dest[b] = '\0';
			}
         }
         else
         {

            char *home;
            home = getenv("HOME");
            chdir(home);
         }
      }

      else
      {
         pid_t newPID; //Generate new PID
        
         char * command;
         const char s[] = " ";

         char *args[512];
 
         command = strtok(initArgs, s); 
         args[0] = command; 
         int numArgs = 1; 
         args[numArgs] = strtok(NULL, s);
   
         //Tokenize
         while (args[numArgs] != NULL)
         {
            numArgs = numArgs + 1;
            args[numArgs]  = strtok(NULL, s);
         }

         if (backgroundProcess == 1) //Check if this is a background process
         {
            newPID = fork(); //Create new background process.
            if (newPID < 0)
            {
               perror("Fork failed.");
               exit(1);
            }
         
            if (newPID == 0) //If this is a child
            {
               int i;
               for (i = 0; i < numArgs; i++)
               {
                  if (inputRedirect == 1) //Check if input should be redirected
                  {
                     //Read file, else print error
                     fd = open(args[numArgs+2], O_RDONLY, 0);
                     if (fd == -1)
                     {
                        printf("smallsh: cannot open %s for input\n", args[numArgs+1]);
                        exit(1);
                     }
                     else
                     {
                        //Execute
                        dup2(fd, STDIN_FILENO);
                        close(fd);
                        execvp(command, &command);
                     }
                  }
   
                  if (outputRedirect == 1) //Check if output should be redirected
                  {
                     //Create file and set permission
                     fd = creat(args[numArgs+2], 0644);
                     if (fd == -1)
                     {
                        printf("smallsh: cannot open %s for input\n", args[numArgs+1]);
                        exit(1);
                     }
                     else
                     {
                        //Execute
                        dup2(fd, STDOUT_FILENO);
                        close(fd);
                        execvp(command, &command);
                     }
                  }
               }
               //Execute command without redirection
               if (inputRedirect == 0 && outputRedirect == 0)
               {
                  execvp(command, args);
               }
               //Invalid command
               printf("%s: no such file or directory\n", command);
            }
            else
            {
               //Store backgroundPIDS in array
               int status_1;
               int process;
               printf("background pid is %d\n", newPID);
               backgroundPIDS[backgroundProcessCount] = newPID;
               backgroundProcessCount = backgroundProcessCount + 1;
               process = waitpid(newPID, &status_1, WNOHANG);
               continue;
            }
         }
         else //This is a foreground process
         {   
            newPID = fork();
            if (newPID < 0)
            {
               perror("Fork failed.");
               exit(1);
            }
            
            if (newPID == 0) //If child
            { 
               int i; 
               for (i = 0; i < numArgs; i++)
               {
                  if (inputRedirect == 1) //If we should redirect input
                  {
                     //Read file, else print error
                     fd = open(args[i+2], O_RDONLY, 0);
                     if (fd == -1)
                     {
                        printf("smallsh: cannot open %s for input\n", args[i+2]);
                        exit(1);
                     }
                     else
                     {
                        //Execute
                        dup2(fd, STDIN_FILENO);
                        close(fd);
                        execvp(command, &command);
                     }
                  }
   
                  if (outputRedirect == 1) 
                  {
                     //Create file, else print error.
                     fd = creat(args[i+2], 0644);
                     if (fd == -1)
                     {
                        printf("smallsh: cannot open %s for input\n", args[i+2]);
                        exit(1);
                     }
                     else
                     {
                        //Execute
                        dup2(fd, STDOUT_FILENO);
                        close(fd);
                        execvp(command, &command);
                     }
                  }
               }
 
               //Execute without redirection
               if (inputRedirect == 0 && outputRedirect == 0)
               {
                  execvp(command, args);
               }
              
               //Invalid command
               printf("%s: no such file or directory\n", command);
            }
            else
            {
               //Check ending processes, set exit code.
               int status_1;
               waitpid(newPID, &status, 0);

               if (WIFEXITED(status_1))
               {
                  exitCode = WEXITSTATUS(status_1);
               }
            }      
         }
      }  
      //Reset flags   
      backgroundProcess = 0;
      inputRedirect = 0;
      outputRedirect = 0;

      signal(SIGINT, SIG_IGN); 
   }
   return 0;

}




