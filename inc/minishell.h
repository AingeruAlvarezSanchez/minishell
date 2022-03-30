/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:08:14 by aalvarez          #+#    #+#             */
/*   Updated: 2022/03/29 16:07:10 by aalvarez         ###   ########.fr       */
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
	int		n_cmds;
}	t_cmds;

/* initial funcions, dedicated to set the 
initial configuration of the program */
void	ft_cpyenv(t_data *data, char **envp);
void	ft_get_path(t_data *data);
void	ft_initials(t_cmds *cmds, t_data *data, char *prompt);

/* quote managing functions */
int		ft_quote_error(t_cmds *cmds, int iref, int jref, int quote);
void	ft_quotes(t_cmds *cmds,__attribute__((unused)) t_data *data, int iref, int jref, int quote);

#endif
