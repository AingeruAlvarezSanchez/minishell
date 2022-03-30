/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:36:57 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/30 17:14:28 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

int	ft_n_commands(char *str)
{
	int	i;
	int comands;

	i = 0;
	comands = 1;
	while (str[i])
	{
		if (str[i++] == '|')
			comands++;
	}
	return comands;
}

void	ft_fill_cmds(char *str, t_cmds *Cmds, t_data *Data)
{
	//int	i;
	
	//i = -1;
	if (ft_strchr(str, '|'))
		Cmds->commands = ft_split(str, '|');
	else
	{
		Cmds->commands = (char **)malloc(sizeof(char *) * 2);
		Cmds->commands[0] = ft_strdup(str);
		Cmds->commands[1] = NULL;
	}
	if (ft_strchr(str, '$'))
		ft_split_dollar(Cmds, Data);

	free(str);
	//while (Cmds->commands[++i])
	//	Cmds->commands[i] = ft_strtrim(Cmds->commands[i], " ");
}

void	ft_commands(char *str, t_cmds *Cmds, t_data *Data)
{
	if (!str)
		return ;

	Cmds->pipes = 0;
	Cmds->dollar = 0;
	Cmds->quotes = 0;
	
	Cmds->n_cmds = ft_n_commands(str);
	ft_fill_cmds(str, Cmds, Data);
	ft_init_exec(Cmds, Data);
}
