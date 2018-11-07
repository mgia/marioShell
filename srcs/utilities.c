/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 21:13:13 by marc              #+#    #+#             */
/*   Updated: 2018/11/06 21:13:14 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_cwd(void)
{
	char	*cwd;
	char	buff[4096 + 1];

	cwd = getcwd(buff, 4096);
	ft_putstr(cwd);
}

void	signal_handler(int n)
{
	if (n == SIGINT)
		exit_shell();
}

void	exit_shell(void)
{
	ft_putstr("Out of coins ~ bye!\n");
	ft_freestrarr(g_envp);
	exit(0);
}

void	ft_freestrarr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	arr = NULL;
}

void	mario(void)
{
	ft_printf("\n               ........\n");
	ft_putendl("             :'        '..");
	ft_putendl("            :**          :");
	ft_putendl("            :**           ':");
	ft_putendl("       :''''''              :");
	ft_putendl("       :....................:");
	ft_putendl("       ...:   : :     : :   :.");
	ft_putendl("      :     ..: :     : :   : :");
	ft_putendl("    :'      :...:   :'  :   : :");
	ft_putendl("    :       ...     :...:   : :");
	ft_putendl("    :       : :           ..: :");
	ft_putendl("     ':'''''   ''':     .'  ..:");
	ft_putendl("       :..........''     :..:");
	ft_putendl("       '..               :");
	ft_printf("         '''':..........:\n\n");
	ft_putendl("  __      ____ _| |__   ___   ___");
	ft_putendl("  \\ \\ /\\ / / _` | '_ \\ / _ \\ / _ \\");
	ft_putendl("   \\ V  V / (_| | | | | (_) | (_) |");
	ft_printf("    \\_/\\_/ \\__,_|_| |_|\\___/ \\___/\n\n");
}
