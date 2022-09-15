
#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <signal.h>
# include <sys/time.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/uio.h>
# include <sys/types.h>
# include "Libft/libft.h"

int		g_exit_status;

typedef struct s_msh_var
{
	char	**own_envp;
	char	*pwd;
	char	*oldpwd;
}	t_msh_var;

/*char *binary; //binary array for error checking
, ex: "ls " should not execute to s_command*/
typedef struct s_command
{
	char	**command;
	char	*bin_path;
	char	**path;
	bool	is_absolute;
}	t_command;

//struct only used for dollar expansion
typedef struct s_dollars
{
	char	*beg;
	char	*final;
	char	*value;
	char	*result;
}	t_dollars;

typedef struct s_command_table
{
	int			*pi;
	int			unipipe;
	int			cmd_count;
	t_command	*commands;
}	t_command_table;

char	**ft_duplicate_environment(char **str);
bool	last_chr_not_pipe(char *str);
int		ft_count_pipes(char *pnt);
int		parser(char *str, t_command_table *table);
bool	generate_command_table(char *str, int cmd_count, t_command_table *table);
int		process_string_quotes(char *not_processed_cmd);
bool	ft_error_print(int errnumb);

/*  Redirections */
int		lexer(t_command_table *table, t_msh_var *msh);
bool	contains_redire(char *command);

/*   Expansions    */
bool	ft_check_dollars(t_command_table *table, int i, int x, t_msh_var *msh);
int		ft_single_dollar(t_command *command, int arr_n, int xref);
void	ft_dollar_expansion(t_command *command, t_msh_var *msh, int arr_n, int xref);
char	*ft_dollar_value(t_command *com, t_msh_var *msh, int a_n, int xref);
void	ft_valuebeg(t_dollars *dollars, t_command *cm, int an, int x);
bool	ft_check_char(t_command *com, int a_n, int i, char *refs);

/* builtins */
void	ft_echo(t_command *command);
void	ft_pwd(void);
void	ft_env(t_msh_var *msh, t_command *command);
int		ft_exit(t_command_table *table, int c_num, int count);
int		ft_isexit(t_command_table *table, int c_num, int count);
bool	ft_cd(t_command *command, t_msh_var *msh, int count);
bool	ft_check_unset(t_command *command, t_msh_var *msh, int c_num, int count);
int		ft_export_check(t_command *command, t_msh_var *msh, int c_num, int count);
bool	ft_check_variable(char *variable);
bool	ft_already_in(char *variable, char **env);
int		ft_parent_builtin(t_command *command, t_msh_var *msh, int count, int c_num);
int		ft_checkparent(t_command *command);
bool	ft_child_builtin(t_command *command, t_msh_var *msh);
void	rl_replace_line(const char *text, int clear_undo);
bool	cd_extension(t_command *command, t_msh_var *msh);
void	ft_getoldpwd(t_msh_var *msh, char *route);
void	ft_getnewpwd(t_msh_var *msh);
void	ft_previous_dir(t_msh_var *msh);
void	ft_firstoldpwd(t_msh_var *msh);
char	*ft_get_home(t_msh_var *msh);

/* Execution */
char	*ft_get_result(t_command *command, int i);
bool	ft_isfinal(t_command_table *table, int i, int count, t_msh_var *msh);
bool	return_binary_path(const char *bin_path, char *binary_check);
char	*reach_bin_path(t_command *command, t_msh_var *msh);
void	*execute(t_command_table *table, t_msh_var *msh);
void	close_and_liberate_execution(t_command_table *table);

/* String utils */
bool	str_contains(char *command, char *str);
bool	str_exactly_contains(char *command, char *str);
void	string_to_lower(char *pnt);
void	ft_freedollar_struct(t_dollars *dollars);
bool	check_if_empty_command(char *str);

/* Binary manage */
char	**get_actual_path(t_msh_var *msh);
bool	gather_bin_path(t_command_table *table, t_msh_var *msh);
bool	ft_check_if_is_accesible(t_command_table *table, int iterate);

/* Signals */
void	ft_check_signal(void);
void	ft_signals(void);
void	ft_signal_exit(void);

/* Pipes managing */
char	*added_pipe(char *str);
bool	clean_double_pipes(char *str);

/* Quotes trimming */
void	ft_trim_algorithm(t_command *command, int i);
void	ft_quotetrim(t_command *command, int i, int final, int j);

/* Free memory */
void	ft_free_commands(t_command_table *table);
void	ft_freedollar_struct(t_dollars *dollars);

/* Error checking */
bool	ft_check_errors(char *str);

#endif