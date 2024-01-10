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
#ifndef MYSHELL_H
#define MYSHELL_H

#define MAX_BUFFER 1024
#define MAX_ARGS 64

extern char **environ;

int cd(char *path); //Change working directory
void clr(); //Clear terminal
void dir(); //List contents of working directory
void environment(char ** env); //Print environment strings
void echo(int arg_count, char ** args); //Echo arguments
void help(); //Open user manual
void pause_shell(); //Pause shell
void execute_command(int arg_count, char **args, int bg); //Execute command

#endif