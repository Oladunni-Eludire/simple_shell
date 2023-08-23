#include "shell.h"

/**
 * list_len - gets the length of linked list
 * @h: pointer to 1st node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t r = 0;

	while (h)
	{
		h = h->next;
		r++;
	}
	return (r);
}

/**
 * list_to_strings - returns an array of strings
 * @head: pointer to 1st node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t r = list_len(head), m;
	char **strs;
	char *str;

	if (!head || !r)
		return (NULL);
	strs = malloc(sizeof(char *) * (r + 1));
	if (!strs)
		return (NULL);
	for (r = 0; node; node = node->next, r++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (m = 0; m < r; m++)
				free(strs[m]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[r] = str;
	}
	strs[r] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a linked list
 * @h: pointer to 1st node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t r = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		r++;
	}
	return (r);
}

/**
 * node_starts_with - returns node with string that starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t r = 0;

	while (head)
	{
		if (head == node)
			return (r);
		head = head->next;
		r++;
	}
	return (-1);
}
