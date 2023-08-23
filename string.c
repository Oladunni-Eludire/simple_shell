#include "shell.h"

/**
 * _strlen - returns length of a string
 * @s: string to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int b = 0;

	if (!s)
		return (0);

	while (*s++)
		b++;
	return (b);
}

/**
 * _strcmp - compares two strings.
 * @s1: 1st string
 * @s2: 2nd string
 *
 * Return: zero if s1 == s2, negative if s1 < s2, positive if s1 > s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: the string to search
 * @needle: substring
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: destination
 * @src: source
 *
 * Return: pointer to destination
 */
char *_strcat(char *dest, char *src)
{
	char *r = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (r);
}
