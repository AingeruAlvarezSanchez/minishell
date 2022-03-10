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

void	ft_ischild_builtin(t_cmds *Cmds, t_data *Data)
{
	if (!ft_strncmp(Cmds->p_command[0], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(Cmds->p_command[0], "echo", 4))
		ft_check_echo(Cmds);
	else if (!ft_strncmp(Cmds->p_command[0], "env", 3))
		ft_env(Data);
}

void	ft_isparent_builtin(t_cmds *Cmds, t_data *Data)
{
	int	i;

	i = -1;
	Cmds->p_command = ft_split(Cmds->commands[0], ' ');
	if (!Cmds->p_command[0])
	{
		while (Cmds->p_command[++i])
			free(Cmds->p_command[i]);
		free(Cmds->p_command);
		return ;
	}
	if (!ft_strncmp(Cmds->p_command[0], "cd", 2))
		ft_cd(Cmds, Data);
	else if (!ft_strncmp(Cmds->p_command[0], "exit", 4))
		ft_exit();
	else if (!ft_strncmp(Cmds->p_command[0], "export", 6))
		ft_check_export(Data, Cmds);
	else if (!ft_strncmp(Cmds->p_command[0], "unset", 5))
		ft_check_unset(Data, Cmds);
	if (Cmds->p_command)
		ft_doublefree(Cmds->p_command);
}

void	ft_execute(t_data *Data, t_cmds *Cmds)
{
	char	*tmp;
	int		i;

	i = -1;
	if (!Cmds->p_command[0])
		exit (0);
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
	if (!ft_strncmp(Cmds->p_command[0], "export", 6))
		return (1);
	else if (!ft_strncmp(Cmds->p_command[0], "unset", 5))
		return (1);
	else if (!ft_strncmp(Cmds->p_command[0], "cd", 2))
		return (1);
	return (0);
}

void	ft_init_exec(t_cmds *Cmds, t_data *Data)
{
	int	i;
	int	status;

	i = 0;
	while (i < Cmds->n_cmds)
	{
		Cmds->p_command = ft_split(Cmds->commands[i], ' '); 
		if (!ft_check_builtin(Cmds)) // checkear aqui el numero de la vuelta en la que se encuentra el comando, si el comando padre no esta en la primera vuelta, no debe eejcutarse
		{
			Cmds->pid = fork();
			if (Cmds->pid == 0)
				ft_execute(Data, Cmds);
			else
				waitpid(Cmds->pid, &status, 0);
		}
		else
			ft_isparent_builtin(Cmds, Data);
		i++;
	}
	i = -1;
	ft_doublefree(Cmds->commands);
}
