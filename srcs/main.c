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
	ft_putstr("Out of coins ~ bye!\n");
	ft_freestrarr(g_envp);
	exit(0);
}

void	signal_handler()
{
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

// char	*check_arg

/*
**	Echo Builtin: Handles complete quotation marks ("arg" => arg), expansions
**	$ for environment variables and ~ for $HOME
*/

void	echo_print(char *arg, int len)
{
	if (!len)
		return ;
	if (len == 1 && arg[0] == '~')
		ft_putstr("get $HOME");
	else if (arg[0] == '$')
		ft_putstr("get $ENV");
	else
		ft_putnstr(arg, len);
}

void	echo_arg(char *arg)
{
	int		i;
	int		len;

	if (!*arg)
		return ;
	len = ft_strlen(arg);
	i = (arg[0] == '\"');
	(i && len > 1 && arg[len - 1] == '\"') ?
		echo_print(arg + i, len - 2) :
		echo_print(arg, len);
}

void	echo(char **args)
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

/*
** find_evnp(): Returns the index if key exists, else returns total length
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
	// ft_freestrarr(g_envp);
	return (res);
}

void	set_envp(char *key, char *value)
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
	ft_printf("[%d] %s (setenv)\n", pos, g_envp[pos]);
	free(tmp);
}

/*
** Setenv Builtin: Adds a variable to envp
*/
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
	set_envp(arg[0], arg[1]);
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

void	execute_command(char **command)
{
	if (!command || !*command || !**command)
		return ;
	else if (!ft_strcmp(command[0], "env"))
		print_env();
	else if (!ft_strcmp(command[0], "exit"))
		exit_shell();
	else if (!ft_strcmp(command[0], "echo"))
		echo(command + 1);
	else if (!ft_strcmp(command[0], "setenv"))
		set_env(command + 1);
	else if (!ft_strcmp(command[0], "unsetenv"))
		unset_env(command + 1);
	// else if (!ft_strcmp(command[0], "cd"))
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
