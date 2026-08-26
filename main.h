#ifndef MAIN_H
#define MAIN_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


extern char **environ;

void print(const char *s);
void print_prompt(void);
void get_line_from_user(char *cmd, size_t size);
void exec_cmd(const char *cmd);



#endif 
