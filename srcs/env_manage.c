/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 21:12:45 by marc              #+#    #+#             */
/*   Updated: 2018/11/06 21:12:52 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_envp(char *key, char *value, int print)
{
	int		pos;
	char	*tmp;

	pos = find_envp(key);
	tmp = ft_strjoin("=", value);
	if (g_envp[pos])
	{
		free(g_envp[pos]);
		if (value)
			g_envp[pos] = ft_strjoin(key, tmp);
		else
			g_envp[pos] = ft_strjoin(key, "=");
	}
	else
	{
		g_envp = realloc_env(pos + 1);
		if (value)
			g_envp[pos] = ft_strjoin(key, tmp);
		else
			g_envp[pos] = ft_strjoin(key, "=");
	}
	if (print)
		ft_printf("[%d] %s (setenv)\n", pos, g_envp[pos]);
	free(tmp);
}

void	unset_envp(int pos)
{
	free(g_envp[pos]);
	g_envp[pos] = NULL;
	while (g_envp[pos + 1])
	{
		g_envp[pos] = ft_strdup(g_envp[pos + 1]);
		free(g_envp[pos + 1]);
		pos++;
	}
	g_envp = realloc_env(pos);
}

void	set_env(char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
		i++;
	if (i != 2)
	{
		ft_putendl("Error: Invalid number of arguments (setenv)");
		return ;
	}
	set_envp(arg[0], arg[1], 1);
}

void	unset_env(char **args)
{
	int		i;
	int		pos;

	if (!args[0])
	{
		ft_putendl("Error: Too few arguments (unsetenv)");
		return ;
	}
	i = -1;
	while (args[++i])
	{
		pos = find_envp(args[i]);
		if (g_envp[pos])
		{
			unset_envp(pos);
			ft_printf("[%d] %s (unsetenv)\n", pos, args[i]);
		}
	}
}
