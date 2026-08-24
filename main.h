#ifndef MAIN_H
#define MAIN_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


extern char **environ;


void print_prompt(void);
char *get_line_from_user(void);



#endif 
