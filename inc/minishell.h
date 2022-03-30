/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:08:14 by aalvarez          #+#    #+#             */
/*   Updated: 2022/03/29 21:43:46 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

typedef struct s_data
{
	char	**env;
	char	**path;
	int		last_out;
}	t_data;

typedef struct s_cmds
{
	pid_t	pid;
	char	**commands;
	int		quotes;
	int		dollar;
	int		pipes;
	char	**p_command;
	int		n_cmds;
}	t_cmds;

/* builtin functions */
void	ft_check_echo(t_cmds *Cmds, t_data *Data);
void	ft_pwd(t_data *Data);
void	ft_env(t_data *Data, t_cmds *Cmds);
void	ft_cd(t_cmds *Cmds, t_data *Data, int cmd_pos);
void	ft_exit(t_cmds *Cmds, t_data *Data, int cmd_pos);
void	ft_check_export(t_data *Data, t_cmds *Cmds, int cmd_pos);
void	ft_check_unset(t_data *Data, t_cmds *Cmds, int cmd_pos);
/* Command execution functions */
void	ft_commands(char *str, t_cmds *Cmds, t_data *Data);
void	ft_init_exec(t_cmds *Cmds, t_data *Data);
/* parser */
void	ft_split_dollar(t_cmds *Cmds, t_data *Data);
/* simple and multiquotes managing */
char	*ft_manage_quotes(char *command);
/* signals */
void	ft_signals_inter();
void	ft_signals();
void	ft_signal_exit();
int		ft_interactive(int inter);

#endif
