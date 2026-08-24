#include "main.h"

/**
 * print_prompt - function prints $
 * 
 * Return: void
 */
void print_prompt(void)
{
if (isatty(STDIN_FILENO))
{
printf("#cisfun$ ");
fflush(stdout);
}
}

/**
 * get_line_from_user - read line from stdin
 * 
 * Return: pointer, or NULL on EOF/error
 */
char *get_line_from_user(void)
{
char *line = NULL;
size_t len = 0;
ssize_t read_bytes;

read_bytes = getline(&line, &len, stdin);

if (read_bytes == -1)
{
free(line);
return (NULL);
}

if (read_bytes > 0 && line[read_bytes -1] == '\n')
line[read_bytes - 1] = '\0';

return (line);
}
/**
 * main - function runs the program 
 * 
 * Return: 0
 */


int main(void)
{
char *line;
char *args[2];
pid_t pid;
int status;

while (1)
{
/*display prompt*/
print_prompt();

/*read line from the user*/
line = get_line_from_user();

/*EOF (ctrl + D) or error*/
if (line == NULL)
{
if (isatty(STDIN_FILENO))
break;
}

if (line[0] == '\0')
{
free(line);
continue;
}

args[0] = line;
args [1] = NULL;

pid = fork();

if (pid == -1)
{
perror("fork faild");
free(line);
exit(EXIT_FAILURE);
}

if (pid == 0)
{
if (execve(args[0], args, NULL) == -1)
{
printf("./shell: No such file or directory\n");
free(line);
exit(1);
}
}
else
{
wait(&status);
}

free(line);
}

return (0);
}
