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

// char	**init_env(char **envp)
// {
//
// }

void	execute_command(char **command)
{
	int i = -1;
	while (command[++i])
		ft_printf("%s ", command[i]);
	ft_putchar('\n');
}

void	execute_commands(char **commands)
{
	int		i;
	char	**command;

	i = -1;
	while (commands[++i])
	{
		command = ft_strsplit(commands[i], ' ');
		rl_bind_key('\t', rl_complete);
		execute_command(command);
		ft_freestrarr(command);
	}
}

int		main(int ac, char **av, char **envp)
{
	char	*line;
	char	**commands;

	(void)ac;
	(void)av;
	(void)envp;
	// init_env(envp);
	while (1)
	{
		signal(SIGINT, signal_handler);
		display_cwd();
		line = readline(SHELL);
		if (!line || !*line)
			continue ;
		add_history(line);
		commands = ft_strsplit(line, ';');
		free(line);
		execute_commands(commands);
		ft_freestrarr(commands);
	}
	return (0);
}
