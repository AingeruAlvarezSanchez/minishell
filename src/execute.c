/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:39:27 by aalvarez          #+#    #+#             */
/*   Updated: 2022/03/10 21:47:57 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>
#include <stdio.h>

void	ft_ischild_builtin(t_cmds *Cmds, t_data *Data)
{
	if (!ft_strncmp(Cmds->p_command[0], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(Cmds->p_command[0], "echo", 4))
		ft_check_echo(Cmds);
	else if (!ft_strncmp(Cmds->p_command[0], "env", 3))
		ft_env(Data);
}

void	ft_isparent_builtin(t_cmds *Cmds, t_data *Data, int cmd_pos)
{
	Cmds->p_command = ft_split(Cmds->commands[0], ' ');
	if (!ft_strncmp(Cmds->p_command[0], "cd", 2))
		ft_cd(Cmds, Data, cmd_pos);
	else if (!ft_strncmp(Cmds->p_command[0], "exit", 4))
		ft_exit(Cmds, cmd_pos);
	else if (!ft_strncmp(Cmds->p_command[0], "export", 6))
		ft_check_export(Data, Cmds, cmd_pos);
	else if (!ft_strncmp(Cmds->p_command[0], "unset", 5))
		ft_check_unset(Data, Cmds, cmd_pos);
	if (Cmds->p_command)
		ft_doublefree((void **)Cmds->p_command);
}

void	ft_pipes(t_cmds *Cmds, int cmd_n)
{
	int	i;

	i = -1;
	while (++i < Cmds->n_cmds + 1)
	{
		if (i != cmd_n)
			close(Cmds->pipefd[i][0]);
		if (i != cmd_n + 1)
			close(Cmds->pipefd[i][1]);
	}
	dup2(Cmds->pipefd[cmd_n][0], 0);
	dup2(Cmds->pipefd[cmd_n + 1][1], 1);
	close(Cmds->pipefd[cmd_n][0]);
	close(Cmds->pipefd[cmd_n + 1][1]);
}

void	ft_execute(t_data *Data, t_cmds *Cmds, int cnum)
{
	char	*tmp;
	int	i;

	i = -1;
	if (!Cmds->p_command[0])
	{
		exit (0);
	}

	if (Cmds->n_cmds > 1)
	{
		dup2(Cmds->pipefd[cnum][1], 1);
		dup2(Cmds->pipefd[cnum + 1][0], 0);
		close(Cmds->pipefd[cnum][0]);
		close(Cmds->pipefd[cnum][1]);
		close(Cmds->pipefd[cnum + 1][0]);
		close(Cmds->pipefd[cnum + 1][1]);
	}
	ft_ischild_builtin(Cmds, Data);
	while (Data->path[++i])
	{
		tmp = ft_strjoin(Data->path[i], Cmds->p_command[0]);
		if (access(tmp, X_OK) == 0)
			execve(tmp, Cmds->p_command, Data->env);
		free(tmp);
	}
	printf("%s: Command not found\n", Cmds->p_command[0]);
	exit(0);
}

int	ft_check_builtin(t_cmds *Cmds)
{
	if (!Cmds->p_command[0])
		return (0);
	if (!ft_strncmp(Cmds->p_command[0], "cd", 2))
		return (1);
	else if (!ft_strncmp(Cmds->p_command[0], "exit", 4))
		return (1);
	else if (!ft_strncmp(Cmds->p_command[0], "export", 6))
		return (1);
	else if (!ft_strncmp(Cmds->p_command[0], "unset", 5))
		return (1);
	return (0);
}

void	ft_pipesmem(t_cmds *Cmds)
{
	int	i;

	i = -1;
	Cmds->pipefd = (int **)malloc(sizeof(int *) * (Cmds->n_cmds + 1));
	while (++i < Cmds->n_cmds + 1)
	{
		Cmds->pipefd[i] = (int *)malloc(sizeof(int) * 2);
		pipe(Cmds->pipefd[i]);
	}
}

void	ft_init_exec(t_cmds *Cmds, t_data *Data)
{
	int	i;
	int	status;

	i = 0;
	if (Cmds->n_cmds > 1)
		ft_pipesmem(Cmds);
	while (i < Cmds->n_cmds)
	{
		Cmds->p_command = ft_split(Cmds->commands[i], ' ');
		if (!ft_check_builtin(Cmds))
		{
			Cmds->pid = fork();
			interactive = 0;

			if (Cmds->pid == 0)
				ft_execute(Data, Cmds, i);
				
			else
				waitpid(Cmds->pid, &status, 0);
		}
		else
		{
			ft_isparent_builtin(Cmds, Data, i);
		}
		i++;
	}
	ft_doublefree((void **)Cmds->commands);
	interactive = 1;
}
