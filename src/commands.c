/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:36:57 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/10 16:10:45 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_commands_n(char *str, t_cmds *Cmds)
{
	int	i;

	i = -1;
	Cmds->n_cmds = 1;
	while (str[++i])
	{
		if (str[i] == '|')
			Cmds->n_cmds++;
	}
	Cmds->pipefd = (int **)malloc(sizeof(int *) * (Cmds->n_cmds + 1));
	i = -1;
	while (++i < Cmds->n_cmds + 1)
	{
		Cmds->pipefd[i] = (int *)malloc(sizeof(int) * 2);
		pipe(Cmds->pipefd[i]);
	}
	i = -1;
	/* while (++i < Cmds->n_cmds + 1)
		free(Cmds->pipefd[i]);
	free(Cmds->pipefd); */ //No usar doublefree para liberar esta variable, da segfault porque no encuentra un NULL
}

void	ft_fill_commands(char *str, t_cmds *Cmds)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	while (str[++i])
	{
		if (str[i] == '|')
			check = 1;
	}
	i = -1;
	if (check == 1)
	{
		Cmds->commands = ft_split(str, '|');
		while (Cmds->commands[++i])
			Cmds->commands[i] = ft_strtrim(Cmds->commands[i], " ");
	}
	else
	{
		Cmds->commands = (char **)malloc(sizeof(char *) * 2);
		Cmds->commands[0] = ft_strdup(str);
		Cmds->commands[1] = NULL;
	}
}

void	ft_commands(char *str, t_cmds *Cmds, t_data *Data)
{
	if (!str)
		return ;
	ft_commands_n(str, Cmds);
	ft_fill_commands(str, Cmds);
	ft_init_exec(Cmds, Data);
}
