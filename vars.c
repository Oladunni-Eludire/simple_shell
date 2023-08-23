#include "shell.h"

/**
 * is_chain - test if current char is a chain delimeter
 * @info: struct of the parameter
 * @buf: the char buffer
 * @p: address of current position in buff
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t r = *p;

	if (buf[r] == '|' && buf[r + 1] == '|')
	{
		buf[r] = 0;
		r++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[r] == '&' && buf[r + 1] == '&')
	{
		buf[r] = 0;
		r++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[r] == ';') /* found end of this command */
	{
		buf[r] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = r;
	return (1);
}

/**
 * check_chain - checks if chaining should continue
 * @info: struct of the parameter
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t r = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			r = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			r = len;
		}
	}

	*p = r;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: struct of the parameter
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int r;
	list_t *node;
	char *p;

	for (r = 0; r < 10; r++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int r = 0;
	list_t *node;

	for (r = 0; info->argv[r]; r++)
	{
		if (info->argv[r][0] != '$' || !info->argv[r][1])
			continue;

		if (!_strcmp(info->argv[r], "$?"))
		{
			replace_string(&(info->argv[r]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[r], "$$"))
		{
			replace_string(&(info->argv[r]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[r][1], '=');
		if (node)
		{
			replace_string(&(info->argv[r]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[r], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
