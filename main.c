#include "main.h"

/**
 * print - function print
 * @s: string to be printed
 * Return: void
 */
void print(const char *s)
{
write(STDOUT_FILENO, s, strlen(s));
}

/**
 * print_prompt - function prints $
 * 
 * Return: void
 */
void print_prompt(void)
{
print("#cisfun$ ");
}

/**
 * get_line_from_user - read line from stdin
 * 
 * Return: pointer, or NULL on EOF/error
 */
char *read_input(void)
{
char *line = NULL;
size_t bufsize = 0;
ssize_t characters_read;

/* getline reads from stdin and returns number of bytes read */
characters_read = getline(&line, &bufsize, stdin);

/* Check for EOF (Ctrl+D) or read error */
if (characters_read == -1)
{
free(line); 
return (NULL);
}

	return (line);
}



/**
 * exec_cmd - function excute command
 * @cmd: command 
 * Return: void
 */ 
void exec_cmd(char *cmd)
{
pid_t child_pid;
int status;
char *args[64];
char *token;
int i = 0;

token = strtok(cmd, " \t\r\n");
while (token != NULL && i < 63)
{
args[i] = token;
token = strtok(NULL, " \t\r\n");
i++;
}
args[i] = NULL;

if (args[0] == NULL)
return;

child_pid = fork();

if (child_pid == -1)
{
perror("fork");
return;
} 
else if (child_pid == 0)
{
if (execve(args[0], args, environ) == -1)
{
fprintf(stderr, "./shell: No such file or directory\n");
exit(127);
}
}
else
{
wait(&status);
}
}

/**
 * main - function runs the program 
 * 
 * Return: 0
 */


int main(void)
{
char *line = NULL; 

while (1)
{
/*display prompt*/
print_prompt();

/*read line from the user*/
line = read_input();
    
/* Handle Ctrl+D (EOF) */
if (line == NULL)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "\n", 1);
break; /* Exit the while loop  */
}

/*exc command*/
exec_cmd(line);

free(line); 
}

return (0);

}

