#include "shell.h"
/**
 * @brief 
 * 
 * @param var 
 * @param fd 
 * @return int 
 */

int print(char *var, int fd)
{
    return (write(fd, var, _strlen(var)));
}