/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 21:13:10 by marc              #+#    #+#             */
/*   Updated: 2018/11/06 21:13:11 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

/*
** Creates new process to run binary file input
*/

int		process(char *ex, char **args)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execve(ex, args, g_envp);
	else if (pid < 0)
	{
		ft_putendl("Fork failed to create new process.");
		return (0);
	}
	else
		wait(&pid);
	return (1);
}

/*
** Checks bins in PATH env for system commands
*/

int		check_bins(char **args)
{
	char	*bin_path;
	char	**path;
	int		i;

	path = ft_strsplit(find_arg("PATH", 4), ':');
	bin_path = ft_strnew(4096);
	i = -1;
	while (path && path[++i])
	{
		ft_strclr(bin_path);
		ft_strcat(bin_path, path[i]);
		args[0][0] == '/' ? 0 : ft_strcat(bin_path, "/");
		ft_strcat(bin_path, args[0]);
		if (access(bin_path, F_OK) != -1)
		{
			process(bin_path, args);
			free(bin_path);
			ft_freestrarr(path);
			return (1);
		}
	}
	free(bin_path);
	ft_freestrarr(path);
	return (0);
}

/*
** Checks if command is a directory, executible or system builtin function,
** and executes the respective action. (change directory or execute file)
*/

int		system_call(char **args)
{
	struct stat f;

	if (lstat(args[0], &f) != -1)
	{
		if (f.st_mode & S_IFDIR)
		{
			change_dir(args[0], 0);
			return (1);
		}
		else if (f.st_mode & S_IXUSR)
			return (process(args[0], args));
	}
	else
		return (check_bins(args));
	return (0);
}
