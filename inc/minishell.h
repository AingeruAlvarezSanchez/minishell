/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 05:41:11 by aalvarez          #+#    #+#             */
/*   Updated: 2022/09/04 23:23:55 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define WRITE 1
# define READ 0

typedef struct s_data {
	char	**env;
	char	**export_env;
    char	**paths;
    int     g_last_out;
}	t_data;

typedef struct s_cmds {
	char	*prompt;
	char	*token_value;
	char	**tokens;
	int		n_cmds;
	char	**binary;
	char	***command;
	int		**pipefd;

    pid_t	pid;

}	t_cmds;

/* builtins */
void	ft_exit(char *flag, t_data *data, int cmd_n, t_cmds *cmds);
void	ft_cd(char *flag, t_data *data, int cmd_pos);
void	ft_check_export(char **command, t_data *data, int cmd_n);
void	ft_check_unset(char **command, t_data *data, int cmd_n);
void	ft_check_echo(char **command);
void	ft_env(t_data *Data);
void	ft_pwd(void);
void	ft_child_builtin(char **command, t_data *Data);

/*dollars*/
int     ft_check_dollars(t_cmds *cmds, t_data *data, int iref, int xref);
void	ft_lastout_dollar(t_cmds *cmds, int iref, int xref, t_data *data);
void	ft_dollar_value(t_cmds *cmds, int iref, int xref);
void	ft_dollar_no_value(t_cmds *cmds, int iref, int xref);
void	ft_dollars(t_cmds *cmds, t_data *data);

/*errors*/
int     ft_pipes_error(t_cmds *cmds, int xref, int check);
int     ft_has_final(t_cmds *cmds, int xref, char c);

/*execute*/
void	ft_child_builtin(char **command, t_data *Data);
void	ft_parent_builtin(char** command, t_data *data, int cmd_n, t_cmds *cmds);
int	    ft_check_parent(char *command);
void	ft_execute(t_data *data, char **command, t_cmds *cmds);
void	ft_create_forks(t_cmds *cmds, t_data *data, int pos);

/*initials*/
void	ft_init_execute(t_cmds *cmds, int pos);
void	ft_createpaths(t_data *data);
void	ft_cpyenv(char **envp, t_data *data);
void	ft_initcmds(t_cmds *cmds);

/*main*/
void	ft_trimemptylines(t_cmds *cmds);
void	ft_lastjoin(t_cmds *cmds);
void	ft_check_builtins(t_cmds *cmds, t_data *data);
void	ft_commands(t_cmds *cmds, t_data *data);
int     main(int argc, char **argv, char **envp);

/*parsing*/
void	ft_noquotes_binary(t_cmds *cmds, int i, int x);
void    ft_binary_exists(t_cmds *cmds, t_data *data, int iref);
void	ft_getbinary(t_cmds *cmds, t_data *data);
void    ft_getCommand(t_cmds *cmds);
void	ft_parsing(t_cmds *cmds, t_data *data);

/*pipes*/
int     ft_find_next_pipe(t_cmds *cmds, int xref);
void	ft_create_pipes(t_cmds *cmds);
int     until_pipe(char ** tokens, int a);
int     ft_pipes(t_cmds *cmds, int xref);

/*quotes*/
void	ft_trimquotes(t_cmds *cmds);
void	ft_isnotfirst(t_cmds *cmds, char **tmp, int xref, int x);
void	ft_checkprevious(t_cmds *cmds, int xref, int x);
int     ft_quotes(t_cmds *cmds, int xref, char c);

/*signals*/
int     ft_interactive(int inter);
void	ft_signal_exit(t_data *data, t_cmds *cmds);
void	interact_signal(int signal);
void	signal_handler(int signal);
void	ft_signals(void);

/*special chars*/
int	    ft_is_special_char(char c);
int	    ft_manage_special_character(t_cmds *cmds, int xref, char c);
int     ft_has_special_char(t_cmds *cmds);
#endif