#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<sys/wait.h>

/*This program lists the contents of the home directory 
 * It is almost exactly 
 * the same as using ls -l ~ on the terminal. It makes use
 * environment variables and the execve function to allow this 
 * to happen. The execve is called inside of a child process
 * which was created through a fork call. The parent in the end
 * reaps  child process through wait() to truly terminate the 
 * child process. More explanation down below.
 *
 *
 *Author: Arif Howlader
 *5/5/2020
 *
 *
*/
void main() {
	pid_t pid;

	int child_status;
    
    //This a the char pointer to an array or char ** or char pointer to pointer
    //This is really the list of environment variables that execve the function 
    //usually expects in its 3rd parameter
    //will require. The reason why I am setting it to null is because 
    //for this specific function I will not need the list of environment variables
    // I will use the getenv function to aquire the path to my home and pass that 
    //as on of my arguements in the argv arguement explained below.
 	char * envp[]={NULL};

 	//This is the char pointer to array(or pointer) argv. THis array will be the second 
 	//parameter of the execvue function. This array is simply 
 	//the arguement list of the execve function. The first index is by convention
 	//the program I would like to execute which here is /bin/ls. The subsequent
 	//indexes are -l and the return value from getenv function call with "HOME" as the 
 	//arguement passed. Because "HOME" is the name of the enviornment variable that equals
 	//the path to most computer's home directory and thus getenv returns the pointer containing 
 	//the string of this path. The argv array also is required to be null terminated thus there is 
 	//a NULL at the end.
    char * argv[]= {"/bin/ls","-l",getenv("HOME"),NULL};
    
    //Calling fork to create the child process. For returns 0 for the child process
    //but if it is a negative value then something has gone wrong and thus we 
    // have to terminate.
	if ((pid = fork()) < 0) {   
		exit(0);
	}
	//This is the child process
	else if (pid == 0) {

	  //Child process executes the execve function but again we 
	  //have to handle for the case if there is a error in this 
	  //function call 
	  //First parameter of the execve function will be the first 
	  //index of the argv array which is /bin/ls. The second parameter 
	  //is the argv array itself containing all the commands for the 
	  // execve function to execute. It has -l and the path to the home and 
	  // is null terminated.
	  if (execve(argv[0], argv, envp) < 0) {
      exit(1);
      } 
   
	} 

	//This is parent process reaping the child process
	wait(&child_status);                                      
                                                     
}                                                                                                 


