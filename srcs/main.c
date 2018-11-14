/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 21:13:06 by marc              #+#    #+#             */
/*   Updated: 2018/11/06 21:13:08 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (!ft_strcmp(command[0], "cd"))
		cd(command + 1);
	else if (ft_strequ(command[0], "mario"))
		mario();
	else if (!system_call(command))
		ft_printf("mario: Command not found: %s\n", command[0]);
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
