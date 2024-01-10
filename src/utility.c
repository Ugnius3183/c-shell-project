/* Student - Ugnius Packevicius
   Student Number - 21455772
   Date - 17/03/2023

I understand that the University regards breaches of academic integrity and plagiarism as grave and serious.

I have read and understood the DCU Academic Integrity and Plagiarism Policy. I accept the penalties that may be imposed should I engage in practice or practices that breach this policy.

I have identified and included the source of all facts, ideas, opinions and viewpoints of others in the assignment references. Direct quotations, paraphrasing, discussion of ideas from books, journal articles, internet sources, module text, or any other source whatsoever are acknowledged and the sources cited are identified in the assignment references.

I declare that this material, which I now submit for assessment, is entirely my own work and has not been taken from the work of others save and to the extent that such work has been cited and acknowledged within the text of my work.

I have used the DCU library referencing guidelines (available at https://www4.dcu.ie/library/classes_and_tutorials/citingreferencing.shtml and/or the appropriate referencing system recommended in the assignment guidelines and/or programme documentation.

By signing this form or by submitting material online I confirm that this assignment, or any part of it, has not been previously submitted by me or any other person for assessment on this or any other course of study.
 
By signing this form or by submitting material for assessment online I confirm that I have read and understood the DCU Academic Integrity and Plagiarism Policy (available at http://www.dcu.ie/registry/examinations/index.shtml).

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "myshell.h"

// Function to change the current working directory
/*Uses chdir with current path to switch to a different directory and throws
  an error if an invalid directory is given.

  References:
    man chdir, perror
    Opengroup.org "Official documentation for unistd.h" https://pubs.opengroup.org/onlinepubs/7908799/xsh/unistd.h.html (accessed March 9 2023)
*/
int cd(char *path){
    int s = chdir(path);
    if(s != 0){
        perror("cd error");
    }
    return 0;
}

// Function to clear the terminal
void clr(){
    system("clear");
}

// Function to print the contents of a directory
void dir(){
    system("ls");
}

// Function to print all environment strings
/*Uses the external environ variable to pass through all environment strings and print them all
  
  References:
    Naman Tamrakar : "Ways to get and set environment variables in C", dev.to https://dev.to/namantam1/ways-to-get-and-set-environment-variables-in-c-200m (accessed March 9 2023)
*/
void environment(char ** env){
    for(int i = 0; env[i] != NULL; ++i){
        printf("%s\n", env[i]);    
    }
}

// Function to echo a string on the display followed by a new line
/*Checks if echo is followed by any arguments, if so then prints args according to the arg count,
  if no arguments are found then nothing is printed
*/
void echo(int arg_count, char ** args){
    if(arg_count > 1){
        for(int i = 1; i < arg_count; ++i){
            printf("%s ", args[i]);
        }
        printf("\n");
    }
}

// Function to display the user manual using the more filter
/*Uses the more filter to find and display the user manual on the terminal

  References:
    man more
    Geeksforgeeks.org "more command in Linux with Examples" https://www.geeksforgeeks.org/more-command-in-linux-with-examples/ (accessed March 9 2023)
*/
void help(){
    system("more readme");
}

// Function to pause the operation of the shell until you press enter
/*Uses getc on stdin to wait until the user presses enter which is equivalent
  to a newline character

  References:
    man getc
*/
void pause_shell(){
    printf("Press ENTER to continue...");
    while (getc(stdin) != '\n');
}

// Function to execute a command
void execute_command(int arg_count, char **args, int bg){

    //Executes change directory function
    if(strcmp(args[0], "cd") == 0){
        if(arg_count > 1){
            cd(args[1]);
        }
        //Changes to home directory if no arguments provided
        else{
            cd(getenv("HOME"));
        }
    }

    //Executes clear function
    else if(strcmp(args[0], "clr") == 0){
        clr();
    }

    //Executes directory contents function
    else if(strcmp(args[0], "dir") == 0){
        if (arg_count > 1) {
            dir(args[1]);
        }
        //Lists contents of current working directory if no arguments passed
        else {
            dir(".");
        }
    }
    
    //Executes environ function
    else if(strcmp(args[0], "environ") == 0){
        environment(environ);
    }
    
    //Executes echo function
    else if(strcmp(args[0], "echo") == 0){
            echo(arg_count, args);
    }
    
    //Executes user manual function
    else if(strcmp(args[0], "help") == 0){
        help();
    }
    
    //Executes the pause shell function
    else if(strcmp(args[0], "pause") == 0){
        pause_shell();
    }
    
    //Executes the quit shell function
    else if(strcmp(args[0], "quit") == 0){
        exit(0);
    }
    
    /*Fork and exec implementation if a command is entered that hasn't been implemented
      
      References:
        man fork, exec, wait
        Geeksforgeeks.org "Difference between fork() and exec()" https://www.geeksforgeeks.org/difference-fork-exec/ (accessed March 11 2023)
    */
    else{
        //Forks a child process
        pid_t pid = fork();
        //Catches errors if the process fails to be created
        if(pid == -1){
            perror("Fork error");
            exit(1);
        }
        //Checks that the forked process is in fact a child process
        else if(pid == 0){
            execvp(args[0], args);
            perror("Execute error");
            exit(1);
        }
        //If the pid hasn't failed but isn't 0
        else{
            if(!bg){ //if background execution isn't found, wait for child process to finish
                waitpid(pid, NULL, 0);
            }
        }
    }
}