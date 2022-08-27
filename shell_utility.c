#include "shell.h"
/**
 * cntrl_c - Signal to implement CTRL+C command
 * 
 * @param signum
 * Return: Signal 
 */

void cntrl_c(int signum)
{
    if (signum == SIGINT)
    {
        print("\n ($) ", STDIN_FILENO);
    }
}

/**
 * @brief 
 * 
 * 
 * Return:
 */
char *get_line(void)
{
    int buff_size = READ_BUFFER, value_read, pointer = 0;
    char *buffer = malloc(buff_size * sizeof(char));
    char c;

    if (buffer == NULL)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        value_read = read(STDIN_FILENO, &c, 1);
        if (c == EOF || !value_read)
        {
            if (isatty(STDIN_FILENO) == 1)
            {
                print("\n", STDIN_FILENO);
                return (NULL);
            }
        }
        else if (c == '\n' || !value_read)
        {
            buffer[pointer] = '\0';
            return (buffer);
        }
        else 
            buffer[pointer] == c;
        pointer++;

        if (pointer >= buff_size)
        {
            buff_size += READ_BUFFER;
            buffer = _realloc(buffer, READ_BUFFER, buff_size);
            if (!buffer)
            {
                perror("Failed to reallocate memory");
                exit(EXIT_FAILURE);
            }
        }

    }
    
}