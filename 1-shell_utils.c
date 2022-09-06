#include "shell.h"

void ctrl_C(int signum)
{
	if (signum == SIGINT)
		print("\n ($) ", STDIN_FILENO);
}

/**
 * _getline - takes input from the user
 *
 * Return: the string read
 */

char *_getline(void)
{
	int bufSize = READ_BUF, no_read, position = 0;

	char *buffer = malloc(bufSize * sizeof(char));
	char c;

	if (buffer == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		no_read = read(STDIN_FILENO, &c, 1);
		if (c == EOF || !no_read)
		{
			/* checks if the input is EOT 
			 	(ctrl+D) and if it is from the terminal
			*/
			if (isatty(STDIN_FILENO) == 1)
			{
				print("\n", STDIN_FILENO);
				return (NULL);
			}
		}
		else if (c == '\n' || !no_read)
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else
			buffer[position] = c;
		position++;

		if (position >= bufSize)
		{
			bufSize += READ_BUF;
			buffer = _realloc(buffer, READ_BUF, bufSize);
			if (!buffer)
			{
				perror("Failed to re-allocate a space in the memory");
				exit(EXIT_FAILURE);
			}
		}
	}
}

int is_delimeter(const char *delimeters, char c);

/**
 * tokenize - split a string
 * @str: string to split
 * @delim: charcter to split str
 * Return: pointer to new or NULL
 */
char **tokenize(char *str, const char *delim)
{
	int k = 0, j = 0, i = 0, size = 0, lens[1200];
	char **arr;

	if (str == NULL || !(*str))
		return (NULL);
	/* calc no of words and lengths */
	for (i = 0; str[i]; i++)
	{
		/* skip delimeters */
		if (is_delimeter(delim, str[i]))
			continue;
		/* get the word length */
		j = i;
		while (!is_delimeter(delim, str[i]) && str[i])
			i++;
		if (i > j)
			lens[size++] = i - j;
		if (!str[i])
			break;
	}
	if (!size)
		return (NULL);
	/* create array of strings */
	arr = malloc((size + 1) * sizeof(char *));
	for (i = 0; str[i]; i++)
	{
		if (is_delimeter(delim, str[i]))
			continue;
		/* copy the word */
		arr[k] = malloc((lens[k] + 1) * sizeof(char));
		j = 0;
		while (!is_delimeter(delim, str[i]) && str[i])
			arr[k][j++] = str[i++];
		arr[k++][j] = '\0';
		if (!str[i])
			break;
	}
	arr[size] = NULL;
	return (arr);
}

/**
 * is_delimeter - check if a character is in delimeter
 *
 * @delimeters: pointer to delimeters
 * @c: character to check
 *
 * Return: 1 for true 0 for false
 */
int is_delimeter(const char *delimeters, char c)
{
	int i = 0;
	if (!delimeters)
		return (0);
	while (delimeters[i])
	{
		if (delimeters[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void shell_execute(char **command, int cmd_type)
{
	int stat;
	pid_t PID;

	if (cmd_type == EXTERNAL_CMD || cmd_type == PATH_CMD)
	{
		PID = fork();

		if (PID == 0)
		{
			execute(command, cmd_type);
		}
		if (PID < 0)
		{
			perror("failed to call fork");
			exit(1);
		}
		else
			wait(&stat);
	}
	else
		execute(command, cmd_type);
}

int check_command(char *command)
{
	int i = 0;
	char *int_cmd[] = {"exit", "cd", "env", NULL};

	while (command[i])
	{
		if (command[i] == '/')
			return (EXTERNAL_CMD);
		i++;
	}

	i = 0;
	while (int_cmd[i] != NULL)
	{
		if (_strcmp(command, int_cmd[i]) == 0)
			return (INTERNAL_CMD);
		i++;
	}

	return (INVALID_CMD);
	
}


void execute(char **commands, int cmd_type)
{
	void (*func)(char **command);

	switch (cmd_type)
	{
		case EXTERNAL_CMD:
			{
				if (execve(commands[0], commands, NULL) == -1)
				{
					perror(_getenv("PWD"));
					exit(2);
				}
				break;
			}
		case INTERNAL_CMD:
			{
				func = get_func(commands[0]);
				func(commands);
				break;
			}
		case PATH_CMD:
			{
				break;
			}
		case INVALID_CMD:
			{
				break;
			}
	}
}
