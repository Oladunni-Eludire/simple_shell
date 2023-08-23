#include "shell.h"

/**
 * _myenv - prints the current environ
 * @info: Struct containing possible arguments.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environment variable
 * @info: Struct containing possible arguments.
 * @name: env variable name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environ variable,
 *             or modify an existing one
 * @info: Struct containing possible arguments.
 * Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Struct containing possible arguments.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int b;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (b = 1; b <= info->argc; b++)
		_unsetenv(info, info->argv[b]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Struct containing possible arguments.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&node, environ[a], 0);
	info->env = node;
	return (0);
}
