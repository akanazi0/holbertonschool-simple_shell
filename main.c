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
void get_line_from_user(char *cmd, size_t size)
{
if (fgets(cmd, size, stdin) == NULL)
{
if (feof(stdin)){
print("\n");
exit(EXIT_SUCCESS);
} else {
print("Error while reading input \n");
exit(EXIT_FAILURE);
}
}
cmd[strcspn(cmd, "\n")] = '\0';
}

/**
 * exec_cmd - function excute command
 * @cmd: command 
 * Return: void
 */ 
void exec_cmd(const char *cmd)
{
pid_t child_pid = fork();

if (child_pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
} 
else if (child_pid == 0)
{
execlp(cmd, cmd, (char *)NULL);
perror("execlp");
exit(EXIT_FAILURE);
}
else
{
wait(NULL);
}
}

/**
 * main - function runs the program 
 * 
 * Return: 0
 */


int main(void)
{
//char *line;
char cmd[100];
//pid_t pid;
//int status;
//char *token;
//int i;

while (1)
{
/*display prompt*/
print_prompt();

/*read line from the user*/
get_line_from_user(cmd, sizeof(cmd));

/*exc command*/
exec_cmd(cmd);
}

return (0);

}

