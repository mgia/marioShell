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
	ft_printf("");
}
