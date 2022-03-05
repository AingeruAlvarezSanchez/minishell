/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:39:27 by aalvarez          #+#    #+#             */
/*   Updated: 2022/03/03 20:02:00 by aalvarez         ###   ########.fr       */
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

void	ft_execute(t_data *Data, t_cmds *Cmds, char *command)
{
	char		*tmp;
	int		i;

	i = -1;
	Cmds->p_command = ft_split(command, ' ');
	if (!Cmds->p_command[0])
		exit (0);
	else if (!ft_strncmp(Cmds->p_command[0], "export", 6))
		exit (0);
	else if (!ft_strncmp(Cmds->p_command[0], "unset", 5))
		exit (0);
	else if (!ft_strncmp(Cmds->p_command[0], "cd", 2))
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

void	ft_init_exec(t_cmds *Cmds, t_data *Data)
{
	int	i;

	i = 0;
	ft_isparent_builtin(Cmds, Data);
	while (i < Cmds->n_cmds)
	{
		Cmds->pid = fork();
		if (Cmds->pid == 0)
			ft_execute(Data, Cmds, Cmds->commands[i]);
		i++;
	}
	i = -1;
	ft_doublefree(Cmds->commands);
}
