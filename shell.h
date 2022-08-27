#ifndef _SHELL_H
#define _SHELL_H

/*initial size of buffer for user input */
#define READ_BUFFER 1000

/* Importing standard libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <signal.h>

/* shell utility functions */
void cntrl_c(int);
char *get_line(void);

/* memory management */
void *_realloc(void *, int, int);

int print(char *, int);
int _strlen(char *);

#endif /* _Shell_H */