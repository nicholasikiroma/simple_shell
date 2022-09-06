#include "shell.h"

int _strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

int _strcmp(char *str1, char *str2)
{
	int len1 = _strlen(str1);
	int len2 = _strlen(str2);
	int i;

	if (len1 != len2)
		return (-1);
	while(str1[i])
	{
		if (str1[i] != str2[i])
			return (-1);
		i++;
	}
	return (0);
}
