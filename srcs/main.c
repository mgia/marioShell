#include "minishell.h"

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

void	exit_shell(void)
{
	ft_freestrarr(g_envp);
	exit(0);
}

void	signal_handler()
{
	ft_putstr("Out of coins ~ bye!\n");
	exit_shell();
}

void	display_cwd(void)
{
	char	*cwd;
	char	buff[4096 + 1];

	cwd = getcwd(buff, 4096);
	ft_putstr(cwd);
}


void	print_env(void)
{
	int i;

	i = -1;
	while (g_envp[++i])
		ft_putendl(g_envp[i]);
}
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

void	execute_command(char **command)
{
	int i = -1;
	while (command[++i])
		if (!ft_strcmp(command[i], "print"))
			print_env();
			// ft_printf("%s ", command[i]);
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

void	entry(void)
{
	ft_printf("Mario - Ready Player One\n");
}

int		main(int ac, char **av, char **envp)
{
	char	*line;
	char	**commands;

	(void)ac;
	(void)av;
	init_env(envp);
	entry();
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
