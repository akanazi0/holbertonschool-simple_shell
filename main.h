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
void get_line_from_user(char *cmd, size_t size);
void exec_cmd(char *cmd, char *prog_name, int count);
char *read_input(void);


#endif 
