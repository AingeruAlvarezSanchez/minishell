/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:11:40 by ecorreia          #+#    #+#             */
/*   Updated: 2022/09/16 21:11:44 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_env
{
	char	**env;
	char	**exp;
	char	*pwd;
	char	*oldpwd;
}	t_env;

typedef struct s_cmd
{
	char	**cmd;
	char	*bin_path;
	char	**path;
	bool	is_absolute;
}	t_cmd;

typedef struct s_dollars
{
	char	*beg;
	char	*final;
	char	*value;
	char	*result;
}	t_dollars;

typedef struct s_cmds_all
{
	int			*pi;
	int			unipipe;
	int			n_cmds;
	t_cmd	*cmds;
}	t_cmds_all;

/* builtins */
void	ft_echo(t_cmd *cmd);
void	ft_pwd(void);
void	ft_env(t_env *msh, t_cmd *command);
int		ft_exit(t_cmds_all *table, int c_num, int count);
int		ft_isexit(t_cmds_all *table, int c_num, int count);
bool	ft_cd(t_cmd *command, t_env *msh, int count);
bool	ft_check_unset(t_cmd *command, t_env *msh, int c_num, int count);
int		ft_export_check(t_cmd *command, t_env *msh, int c_num, int count);
bool	ft_check_variable(char *variable);
bool	ft_already_in(char *variable, char **env);
int		ft_parent_builtin(t_cmd *command, t_env *msh, int count, int c_num);
int		ft_checkparent(t_cmd *command);
bool	ft_child_builtin(t_cmd *command, t_env *msh);
void	rl_replace_line(const char *text, int clear_undo);
bool	cd_extension(t_cmd *command, t_env *msh);
void	ft_getoldpwd(t_env *msh, char *route);
void	ft_getnewpwd(t_env *msh);
void	ft_previous_dir(t_env *msh);
void	ft_firstoldpwd(t_env *msh);
char	*ft_get_home(t_env *msh);
void	ft_create_exp_var(char *variable, t_env *msh);

//ENVIROMENT
char	**ft_dup_env(char **env);

//PARSER
bool	ft_last_nopipe(char *prompt);
int		ft_n_pipes(char *prompt);
int		ft_parser(char *prompt, t_cmds_all *cmds);
bool	ft_create_cmds(char *prompt, int n_cmds, t_cmds_all *cmds);


/*  Redirections */
int		lexer(t_cmds_all *cmds, t_env *msh);//todo
bool	ft_has_redir(char *command);

/*   Expansions    */
bool	ft_check_dollars(t_cmds_all *table, int i, int x, t_env *msh);
int		ft_single_dollar(t_cmd *command, int arr_n, int xref);
void	ft_dollar_expansion(t_cmd *command, t_env *msh, int arr_n, int xref);
char	*ft_dollar_value(t_cmd *com, t_env *msh, int a_n, int xref);
void	ft_valuebeg(t_dollars *dollars, t_cmd *cm, int an, int x);
bool	ft_check_char(t_cmd *com, int a_n, int i, char *refs);


/* Execution */
char	*ft_get_result(t_cmd *command, int i);
bool	ft_isfinal(t_cmds_all *table, int i, int count, t_env *msh);
bool	return_binary_path(const char *bin_path, char *binary_check);
char	*reach_bin_path(t_cmd *command, t_env *msh);
void	*execute(t_cmds_all *table, t_env *msh);
void	close_and_liberate_execution(t_cmds_all *table);



/* Binary manage */
char	**get_actual_path(t_env *msh);
bool	gather_bin_path(t_cmds_all *table, t_env *msh);
bool	ft_check_if_is_accesible(t_cmds_all *table, int iterate);

/* Signals */
void	ft_check_signal(void);
void	ft_signals(void);
void	ft_signal_exit(void);

/* Pipes managing */
char	*added_pipe(char *str);
bool	clean_double_pipes(char *str);

/* Quotes trimming */
void	ft_trim_algorithm(t_cmd *command, int i);
void	ft_quotetrim(t_cmd *command, int i, int final, int j);

/* Free memory */
void	ft_free_commands(t_cmds_all *table);
void	ft_freedollar_struct(t_dollars *dollars);

//UTILS
/* error*/
bool	ft_check_errors(char *str);
bool	ft_print_err(int error);
//STRING ERRORS
int		ft_process_quotes(char *raw_cmd);
/* String utils */
bool	str_contains(const char *cmd, char *str);
bool	ft_str_has(char *command, char *str);
void	string_to_lower(char *pnt);
void	ft_freedollar_struct(t_dollars *dollars);
bool	check_if_empty_command(char *str);



#endif