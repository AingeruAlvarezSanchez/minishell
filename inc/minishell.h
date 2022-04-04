/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:08:14 by aalvarez          #+#    #+#             */
/*   Updated: 2022/04/04 04:10:03 by aalvarez         ###   ########.fr       */
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
	char	**tokens;
	char	**commands;
	int		n_cmds;
}	t_cmds;

/* initial funcions, dedicated to set the 
initial configuration of the program */

void	ft_cpyenv(t_data *data, char **envp);
void	ft_get_path(t_data *data);
void	ft_initials(t_cmds *cmds, t_data *data, char *prompt);

/* quote managing functions */

int		ft_quote_error(t_cmds *cmds, int iref, int jref, int quote);
void	ft_quotes(t_cmds *cmds, int iref, int jref, int quote);

/* parsing functions */

void	ft_check_dollar(t_cmds *cmds, t_data *data, int iref, int jref);
int		ft_check_pipes(t_cmds *cmds, int iref, int jref);
void	ft_parser(t_cmds *cmds);
void	ft_mono_command(t_cmds *cmds);

/* signals */

void	ft_signals_inter();
void	ft_signals();
void	ft_signal_exit(t_cmds *cmds);
int		ft_interactive(int inter);

#endif