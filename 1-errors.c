#include "shell.h"

/**
 * _erratoi - converts string to integer
 * @s: string
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *s)
{
	int b = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (b = 0;  s[b] != '\0'; b++)
	{
		if (s[b] >= '0' && s[b] <= '9')
		{
			result *= 10;
			result += (s[b] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @info: info parameter & return struct
 * @estr: string containing error type specifation
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function prints a decimal number
 * @input: input
 * @fd: the file descriptor to write to
 *
 * Return: number of char printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int t, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (t = 1000000000; t > 1; t /= 10)
	{
		if (_abs_ / t)
		{
			__putchar('0' + current / t);
			count++;
		}
		current %= t;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converts numbers
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - replaces 1st instance of '#' with '\0'
 * @buf: address to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int t;

	for (t = 0; buf[t] != '\0'; t++)
		if (buf[t] == '#' && (!t || buf[t - 1] == ' '))
		{
			buf[t] = '\0';
			break;
		}
}
