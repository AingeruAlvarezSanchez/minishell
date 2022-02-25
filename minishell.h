/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:08:14 by aalvarez          #+#    #+#             */
/*   Updated: 2022/02/17 18:54:52 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "libft/libft.h"


typedef struct s_data
{
	char	**env;
	char	**path;
}	t_data;

typedef struct s_cmds
{
	pid_t	pid;
	char	**commands;
	char	**p_command;
	int	n_cmds;
}	t_cmds;

void	ft_commands(char *str, t_cmds *Cmds, t_data *Data);

#endif
