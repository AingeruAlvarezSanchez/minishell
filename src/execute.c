/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:50:38 by aalvarez          #+#    #+#             */
/*   Updated: 2022/04/27 14:54:09 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_execute(t_data *data, t_cmds *cmds)
{
	char	*tmp;
	int		i;

	i = -1;
	while (data->path[++i])
	{
		if (access(cmds->proccess[0], X_OK) == 0)
			execve(cmds->proccess[0], cmds->proccess, data->env);
		tmp = ft_strjoin(data->path[i], cmds->proccess[0]);
		if (access(tmp, X_OK) == 0)
			execve(tmp, cmds->proccess, data->env);
		free(tmp);
	}
	printf("%s: Command not found\n", cmds->proccess[0]);
	exit(0);
}

void	ft_init_execute(t_cmds *cmds, int pos)
{
	if (cmds->n_cmds != 1)
	{
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
		ft_init_execute(cmds, pos);
		close(cmds->pipefd[0][READ]);
		close(cmds->pipefd[0][WRITE]);
		close(cmds->pipefd[1][READ]);
		close(cmds->pipefd[1][WRITE]);
		ft_execute(data, cmds);
	}
}

/**
 * @brief This function checks if the commands are parent or
 * child builtins and sends them to their corresponding handlers
 */
void	ft_check_builtins(t_cmds *cmds, t_data *data)
{
	int	i;
	int	status;

	status = 0;
	pipe(cmds->pipefd[0]);
	pipe(cmds->pipefd[1]);
	i = -1;
	while (++i < cmds->n_cmds)
	{
		if (ft_strchr(cmds->commands[i], '"'))
		{
			cmds->proccess = ft_split(cmds->commands[i], '"');
			if (cmds->proccess[1])
				cmds->proccess[0] = ft_strtrim(cmds->proccess[0], " ");
		}
		else
			cmds->proccess = ft_split(cmds->commands[i], ' ');
		if (!ft_check_parent(cmds))
		{
			ft_create_forks(cmds, data, i);
			if (cmds->n_cmds > 2)
			{
				close(cmds->pipefd[0][0]);
				close(cmds->pipefd[0][1]);
				waitpid(cmds->pid, &status, 0);
				cmds->pipefd[0][0] = cmds->pipefd[1][0];
				cmds->pipefd[0][1] = cmds->pipefd[1][1];
				pipe(cmds->pipefd[1]);
			}
		}
		else
			ft_parent_builtin(cmds, data, i);
		ft_doublefree(cmds->proccess);
	}
	close(cmds->pipefd[0][READ]);
	close(cmds->pipefd[0][WRITE]);
	close(cmds->pipefd[1][READ]);
	close(cmds->pipefd[1][WRITE]);
	data->last_out = WEXITSTATUS(status);
	ft_doublefree(cmds->commands);
}
