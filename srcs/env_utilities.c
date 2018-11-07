/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 21:13:01 by marc              #+#    #+#             */
/*   Updated: 2018/11/06 21:13:03 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	g_envp = (char **)ft_memalloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		g_envp[i] = ft_strdup(envp[i]);
}

void	print_env(void)
{
	int i;

	i = -1;
	while (g_envp[++i])
		ft_putendl(g_envp[i]);
}

char	**realloc_env(int len)
{
	char	**res;
	int		i;

	res = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	i = -1;
	while (g_envp[++i] && i < len)
	{
		res[i] = ft_strdup(g_envp[i]);
		free(g_envp[i]);
	}
	free(g_envp);
	g_envp = NULL;
	return (res);
}
