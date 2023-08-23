#include "shell.h"

/**
 * hsh - main shell
 * @info: info parameter & return struct
 * @av: argument entered
 *
 * Return: 0 on success, 1 on error
 */
int hsh(info_t *info, char **av)
{
	ssize_t a = 0;
	int builtin_ret = 0;

	while (a != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		a = get_input(info);
		if (a != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a command that is builtin
 * @info: info parameter & return struct
 *
 * Return: -1 if no builtin command is found,
 * 0 if builtin is successfully executed,
 * 1 if builtin found but not executed,
 * 2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int c, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (c = 0; builtintbl[c].type; c++)
		if (_strcmp(info->argv[0], builtintbl[c].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[c].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds the command in PATH
 * @info: info parameter & return struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int c, d;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (c = 0, d = 0; info->arg[c]; c++)
		if (!is_delim(info->arg[c], " \t\n"))
			d++;
	if (!d)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks an exec thread to run command
 * @info: info parameter & return struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
