#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define RED	"\x1B[31m"
# define WHITE	"\x1B[0m"
# define SHELL " "RED"mario"WHITE"Shell: "

char	**g_envp;
#endif

/*
**	Fork functions
*/

int		process(char *ex, char **args);
int		check_bins(char **args);
int		system_call(char **args);

/*
**	Builtin functions
*/

void	change_dir(char *path, int print);
void	cd(char **args);
void	echo(char **args);
void	set_env(char **arg);
void	unset_env(char **args);


/*
**	Environment Management functions
*/

void	init_env(char **envp);
void	print_env(void);
char	**realloc_env(int len);
void	set_envp(char *key, char *value, int print);
void	unset_envp(int pos);
char	*find_arg(char *key, int len);
int		find_envp(char *key);

/*
**	Utilities
*/

void	display_cwd(void);
void	signal_handler(int n);
void	ft_freestrarr(char **arr);
void	exit_shell(void);
void	mario(void);
