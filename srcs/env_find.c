/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 21:12:40 by marc              #+#    #+#             */
/*   Updated: 2018/11/06 21:12:42 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Returns value if key exists, else returns empty string
*/

char	*find_arg(char *key, int len)
{
	int		i;

	i = -1;
	while (g_envp[++i])
		if (!ft_strncmp(g_envp[i], key, len))
			return (g_envp[i] + len + 1);
	return ("");
}

/*
** Returns the index if key exists, else returns total length
*/

int		find_envp(char *key)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(key);
	while (g_envp[++i])
		if (!ft_strncmp(g_envp[i], key, len))
			return (i);
	return (i);
}
