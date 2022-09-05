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

int	g_last_out;

typedef struct s_data {
	char	**env;
	char	**export_env;
}	t_data;

typedef struct s_cmds {
	char	*prompt;
	char	*token_value;
	char	**tokens;
	int		n_cmds;
	char	**binary;
	char	***command;
	int		**pipefd;
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
void	ft_parsing(t_cmds *cmds);

#endif