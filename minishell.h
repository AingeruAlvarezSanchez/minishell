/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:08:14 by aalvarez          #+#    #+#             */
/*   Updated: 2022/02/17 17:39:15 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_data
{
	char **env;
	char **path;
}	t_data;

typedef struct s_cmds
{
	char	*tmp;
	char	*tmp2;
	char	**command;
	char	**route;
	int		n_cmds;
	int		cnum;
	int		i;
}	t_cmds;

typedef struct s_fds
{
	int		**pipefd;
	pid_t	*pid;
}	t_fds;

int	pipex(int argc, char **argv, char **envp);

#endif