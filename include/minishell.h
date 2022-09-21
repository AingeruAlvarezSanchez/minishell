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
# include "Libft/libft.h"
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

int		g_exit;

typedef struct s_cmd
{
    bool	absolute;
    char	**cmd;
    char	**path;
    char	*bin_pth;
}	t_cmd;

typedef struct s_cmds_all
{
    t_cmd	    *cmds;
    int			*pipes;
    int			sngl_pipe;
    int			n_cmds;
}	t_cmds_all;

typedef struct s_dollar
{
    char	*final;
    char	*pre;
    char	*last;
    char	*val;
}	t_dollar;

typedef struct s_env
{
	char	*oldpwd;
	char	*pwd;
	char	**exp;
	char	**env;
}	t_env;

/* builtins */
bool	ft_home_cd(t_cmd *cmd, t_env *env, int pos_cmd);
bool	ft_cd(t_cmd *cmd, t_env *env);
void	ft_echo(t_cmd *cmd);
void	ft_pwd(void);
void	ft_env(t_env *env, t_cmd *cmd);
int		ft_exit(t_cmds_all *cmds, int pos_cmd, int n_cmds);
int		ft_is_exit(t_cmds_all *cmds, int pos_cmd, int n_cmds);
bool	ft_check_unset(t_cmd *cmd, t_env *env, int pos_cmd, int n_cmds);
int		ft_export_check(t_cmd *cmd, t_env *env, int pos_cmd, int n_cmds);
bool	ft_check_variable(const char *var);
bool	ft_already_in(char *var, char **cpy_env);
int		ft_parent_builtin(t_cmd *cmd, t_env *env, int n_cmds, int pos_cmd);
int		ft_checkparent(t_cmd *cmd);
bool	ft_child_builtin(t_cmd *cmd, t_env *env);
void	ft_rewrite_pwd(t_env *env);
void	ft_last_dir(t_env *env);
void	ft_oldpwd(t_env *env);
void	ft_create_exp_var(char *var, t_env *env);
char	**ft_dup_env(char **env);

/*EXEC*/
char	*ft_cpy_path(t_cmd *cmd, int pos);
bool	ft_final_cmd(t_cmds_all *cmds, int n_cmds, int n_cmd, t_env *env);
bool	ft_check_path(const char *path, char *binary);
void	*ft_exec(t_cmds_all *cmds, t_env *env);
char	*ft_bin_path(t_cmd *cmd, t_env *env);
char	**ft_rewrite_path(t_env *env);
bool	ft_get_path(t_cmds_all *cmds, t_env *env);
bool	ft_last_nopipe(const char *prompt);
int		ft_parser(char *prompt, t_cmds_all *cmds);

/*SIGNALS*/
void	ft_check_sig(void);
void	ft_signals(void);
void	ft_sig_exit(void);

/*SPECIALS*/
char	*ft_pipe_add(char *prompt);
bool	ft_has_redir(char *cmd);
void	ft_trim_algorithm(t_cmd *cmd, int x);
void	ft_trim_quot(t_cmd *cmd, int x, int next, int y);
bool	ft_check_dollars(t_cmds_all *cmds, int y, int x, t_env *env);
int		ft_single_dollar(t_cmd *cmd, int x, int c);
void	ft_dollar_expansion(t_cmd *cmd, t_env *env, int x, int xref);
char	*ft_dollar_value(t_cmd *cmd, t_env *env, int x, int xref);
void	ft_valuebeg(t_dollar *dollar, t_cmd *cmd, int x, int xref);
bool	ft_check_char(t_cmd *cmd, int x, int c, const char *specials);

/*UTILS*/
void	ft_free_commands(t_cmds_all *cmds);
bool	ft_check_errors(char *prompt);
bool	ft_print_err(int error);
bool	ft_check_access(t_cmds_all *cmds, int pos_cmd);
int		ft_process_quotes(char *raw_cmd);
bool	FT_str_contains(const char *cmd, char *str);
bool	ft_str_has(char *cmd, char *str);
void	ft_strtolower(char *str);
void	ft_struct_free(t_dollar *dollar);
bool	ft_check_null_cmd(char *cmd);
void	ft_free_exec(t_cmds_all *cmds);

#endif