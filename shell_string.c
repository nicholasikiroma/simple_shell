#include "shell.h"

/**
 * @brief 
 * 
 * @param str 
 * @return int 
 */

int _strlen(char *str)
{
    int i = 0;

    while(str[i])
    {
        i++;
    }
    return (i);
}