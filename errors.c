#include "shell.h"

/**
 * _eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int t = 0;

	if (!str)
		return;
	while (str[t] != '\0')
	{
		_eputchar(str[t]);
		t++;
	}
}

/**
 * _eputchar - writes the char c to stderr
 * @c: The char to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(2, buf, t);
		t = 0;
	}
	if (c != BUF_FLUSH)
		buf[t++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(fd, buf, t);
		t = 0;
	}
	if (c != BUF_FLUSH)
		buf[t++] = c;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int t = 0;

	if (!str)
		return (0);
	while (*str)
	{
		t += _putfd(*str++, fd);
	}
	return (t);
}
