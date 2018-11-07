/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 21:12:32 by marc              #+#    #+#             */
/*   Updated: 2018/11/06 21:12:38 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Echo Builtin: Handles complete quotation marks ("arg" => arg), expansions
**	$ for environment variables and ~ for $HOME
*/

static void	echo_print(char *arg, int len)
{
	if (!len)
		return ;
	if (len == 1 && arg[0] == '~')
		ft_printf("%s", find_arg("HOME", 4));
	else if (arg[0] == '$')
		ft_printf("%s", find_arg(&arg[1], ft_strlen(arg) - 1));
	else
		ft_putnstr(arg, len);
}

static void	echo_arg(char *arg)
{
	int		i;
	int		j;
	int		len;

	if (!*arg)
		return ;
	i = (arg[0] == '\"');
	len = ft_strlen(arg);
	j = (len > 1 && arg[len - 1] == '\"');
	echo_print(arg + i, len - (i + j));
}

void		echo(char **args)
{
	int 	nl;
	int		i;

	if (!args || !*args)
	{
		ft_printf("\n");
		return ;
	}
	nl = !ft_strcmp(args[0], "-n") ? 1 : 0;
	i = nl ? 0 : -1;
	while (args[++i])
	{
		echo_arg(args[i]);
		args[i + 1] ? ft_putchar(' ') : 0;
	}
	!nl ? ft_putchar('\n') : 0;
}
