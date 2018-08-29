#include "minishell.h"

void	exit_shell(void)
{
	ft_putstr("free\n");
	exit(0);
}

void	signal_handler()
{
	ft_putstr("bye\n");
	exit_shell();
}

void	display_cwd(void)
{
	char	*cwd;
	char	buff[4096 + 1];

	cwd = getcwd(buff, 4096);
	ft_putstr(cwd);
	// free(cwd);
}

int		main(int ac, char **av)
{
	char *line;

	(void)ac;
	(void)av;
	while (1)
	{
		signal(SIGINT, signal_handler);
		display_cwd();
		line = readline(SHELL);
		if (!line || !*line)
			continue ;
		add_history(line);
		ft_printf("Command: %s\n", line);
	}
	return (0);
}
