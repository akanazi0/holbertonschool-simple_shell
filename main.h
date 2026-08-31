#ifndef MAIN_H
#define MAIN_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/* Prompt and Input Functions */
void print(const char *s);
void print_prompt(void);
char *read_input(void);

/* Parsing */
char **tokenize_input(char *line);

/* Command Execution */
void exec_cmd(char *cmd, char *prog_name, int count);

#endif /* MAIN_H */
