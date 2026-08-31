#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/* Display & Input */
void print(const char *s);
void print_prompt(void);
char *read_input(void);

/* Parsing */
char **tokenize_input(char *line);

/* Execution */
void exec_cmd(char **args, char *prog_name, int count);

/* Path Resolution */
char *_getenv(const char *name);

/* String Utility Helpers */
int _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
char *_strdup(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);

#endif /* MAIN_H */
