/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:36:57 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/28 21:12:00 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

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



void	ft_fill_cmds(char *str, t_cmds *Cmds, __attribute__((unused)) t_data *Data)
{
	int	i;

	i = -1;
	Cmds->commands = (char **)malloc(sizeof(char *) * 2);
	Cmds->commands[0] = ft_strdup(str);
	Cmds->commands[1] = 0;
	Cmds->dollar = 0;
	Cmds->quotes = 0;
	ft_check_separators(Cmds, Data);
	i = -1;
	while (Cmds->commands[++i])
		Cmds->commands[i] = ft_strtrim(Cmds->commands[i], " ");
}

void	ft_commands(char *str, t_cmds *Cmds, t_data *Data)
{
	if (!str)
	ft_commands_n(str, Cmds);
	ft_fill_cmds(str, Cmds, Data);
	exit(0);
	//ft_fill_commands(str, Cmds);
	ft_init_exec(Cmds, Data);
}
