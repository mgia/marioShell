/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 21:12:17 by marc              #+#    #+#             */
/*   Updated: 2018/11/06 21:12:23 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(char *path, int print)
{
	char	*cwd;
	char	buf[4096 + 1];

	cwd = getcwd(buf, 4096);
	if (!chdir(path))
	{
		if (print)
			ft_putendl(path);
		set_envp("OLDPWD", cwd, 0);
	}
	else
	{
		ft_printf("cd: %s: ", path);
		if (access(path, F_OK) == -1)
			ft_putendl("no such file or directory");
		else if (access(path, R_OK) == -1)
			ft_putendl("permission denied");
		else
			ft_putendl("not a directory");
	}
}

void	cd(char **args)
{
	if (!args[0] || ft_strequ(args[0], "~") || ft_strequ(args[0], "--"))
		change_dir(find_arg("HOME", 4), 0);
	else if (ft_strequ(args[0], "-"))
		change_dir(find_arg("OLDPWD", 6), 1);
	else
		change_dir(args[0], 0);
}
