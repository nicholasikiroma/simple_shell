#include "shell.h"

/**
 * main - Basic Linux  Shell 
 * 
 * @argc: 
 * @pargv: 
 * Return: 
 */

int main (int argc __attribute__((unused)), char **argv)
{
    char *line;
    (void) argv;

    signal(SIGINT, cntrl_c);
    print(" ($) ", STDOUT_FILENO); 

    while (1)
    {
        print(" ($) ", STDOUT_FILENO);
        line = get_line();
    }
    
}