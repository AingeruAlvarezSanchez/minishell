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

void	ft_cpyenv(char **envp, t_data *data);
void	ft_initcmds(t_cmds *cmds);
void	ft_signal_exit(t_data *data, t_cmds *cmds);
int		ft_interactive(int inter);
int		ft_has_special_char(t_cmds *cmds);
int		ft_has_final(t_cmds *cmds, int xref, char c);
int		ft_pipes_error(t_cmds *cmds, int xref, int check);
int		ft_quotes(t_cmds *cmds, int xref, char c);
int		ft_pipes(t_cmds *cmds, int xref);
void	ft_dollars(t_cmds *cmds, t_data *data);
void	ft_parsing(t_cmds *cmds, t_data *data);

/* builtins */
void	ft_exit(char *flag, t_data *data, int cmd_n, t_cmds *cmds);
void	ft_cd(char *flag, t_data *data, int cmd_pos);
void	ft_check_export(char **command, t_data *data, int cmd_n);
void	ft_check_unset(char **command, t_data *data, int cmd_n);
void	ft_check_echo(char **command);
void	ft_env(t_data *Data);
void	ft_pwd(void);
void	ft_child_builtin(char **command, t_data *Data);

/*signals*/
void	ft_signals(void);
int     ft_interactive(int inter);
void	ft_signal_exit(t_data *data, t_cmds *cmds);

#endif