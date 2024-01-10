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
#include "myshell.h"

int main(int argc, char * argv[]){
    /*These 3 lines below set the environment variable 'shell' to the full path of the myshell
      executable by using argv[0] as a way to obtain program name and uses the realpath()
      function to acquire the full path of the executable.

      References:
        man realpath, setenv
        Naman Tamrakar : "Ways to get and set environment variables in C", dev.to https://dev.to/namantam1/ways-to-get-and-set-environment-variables-in-c-200m (accessed March 12 2023)
    */
    char path[1024];
    realpath(argv[0], path);
    setenv("shell", path, 1);
    char command[MAX_BUFFER];
    char *args[MAX_ARGS];
    int arg_count;
    int bg;
    /*The entire if statement below is made to detect and run the contents of a batchfile,
      it checks if there is more than one argument in the invocation and if it finds there
      is then it opens the batchfile in read mode, first checking and replacing any trailing newline
      characters from the ends of commands, including the windows \r character. Then the command
      is tokenised into its arguments and stored in an array, acquiring the argument count along
      the way. After the command is fully prepped then the execute command function can be executed
      and it either moves to the next command in the batchfile or encounters a NULL character ie. no
      more files are left to run so the batchfile is closed and exits out of the program.

      References:
        man fopen, fclose
        Opengroup.org "Official documentation for string.h" https://pubs.opengroup.org/onlinepubs/7908799/xsh/string.h.html (accessed March 12 2023)
    */
    if(argc == 2){
        FILE *batchfile = fopen(argv[1], "r");

        char command[MAX_BUFFER];
        while(fgets(command, sizeof(command), batchfile) != NULL) {
            if(command[strlen(command) - 1] == '\n'){
                command[strlen(command) - 1] = '\0';
            }
            if(command[strlen(command) - 1] == '\r'){
                command[strlen(command) - 1] = '\0';
            }
            if(command[strlen(command) - 1] == '&'){
                bg = 1;
                command[strlen(command) - 1] = '\0';
            }

            char *token = strtok(command, " ");
            arg_count = 0;

            while(token != NULL && arg_count < 10){
                args[arg_count++] = token;
                token = strtok(NULL, " ");
            }
            args[arg_count] = NULL;

            //Run command
            execute_command(arg_count, args, bg);
        }
        fclose(batchfile);
        exit(0);
    }

    //While loop runs indefinitely until it is broken
    while(1){
        /*Using the getcwd function, I am able to make my command line prompt the full path of
          my current working directory which changes as you use the cd function to move to new
          directories.

          References:
            man getcwd
        */
        getcwd(path, sizeof(path));
        printf("user@DESKTOP-ID:%s$ ", path);
        fgets(command, MAX_BUFFER, stdin);

        // Remove trailing newline character from command
        if(command[strlen(command) - 1] == '\n'){
            command[strlen(command) - 1] = '\0';
        }
        if(command[strlen(command) - 1] == '&'){
            bg = 1;
            command[strlen(command) - 1] = '\0';
        }

        // Split command into arguments
        char *token = strtok(command, " ");
        arg_count = 0;

        while(token != NULL && arg_count < 10){
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;

        //Run command
        execute_command(arg_count, args, bg);
    }
    return 0;
}
