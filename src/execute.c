/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:54:41 by ecorreia          #+#    #+#             */
/*   Updated: 2022/06/14 17:25:03 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>


void	ft_execute(t_data *data, char **command)
{
	char	*tmp;
	int		i;

	i = -1;
    //updatePath(data);
	while (data->paths[++i])
	{
		if (access(command[0], X_OK) == 0)
			execve(command[0], command, data->env);
		tmp = ft_strjoin(data->paths[i], command[0]);
		if (access(tmp, X_OK) == 0)
			execve(tmp, command, data->env);
		free(tmp);
	}
	printf("%s: Command not found\n", command[0]);
	exit(0);
}

void	ft_init_execute(t_cmds *cmds, int pos)
{
	if (cmds->n_cmds != 1)
	{	
		if (cmds->redir_flag == pos)
			dup2(cmds->redir_fd, STDOUT_FILENO);
		if (pos == 0)
		{
			if (cmds->n_cmds > 2)
				dup2(cmds->pipefd[1][WRITE], STDOUT_FILENO);
			else
				dup2(cmds->pipefd[0][WRITE], STDOUT_FILENO);
		}
		else if (pos != 0 && pos != cmds->n_cmds - 1)
		{
			dup2(cmds->pipefd[1][WRITE], STDOUT_FILENO);
			dup2(cmds->pipefd[0][READ], STDIN_FILENO);
		}
		else if (pos == cmds->n_cmds - 1)
			dup2(cmds->pipefd[0][READ], STDIN_FILENO);
	}
}

/**
 * @brief This function creates all the necesary forks
 * in order to execute every command
 * 
 * @param pos command number
 */
void	ft_create_forks(t_cmds *cmds, t_data *data, int pos)
{
	cmds->pid = fork();
	ft_interactive(0);
	if (cmds->pid == 0)
	{
        //ft_child_builtin(cmds->command[0], data);
		ft_init_execute(cmds, pos);
		close(cmds->pipefd[0][READ]);
		close(cmds->pipefd[0][WRITE]);
		close(cmds->pipefd[1][READ]);
		close(cmds->pipefd[1][WRITE]);
		ft_execute(data, cmds->command[pos]);
	}
}
