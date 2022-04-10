/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 06:40:11 by aalvarez          #+#    #+#             */
/*   Updated: 2022/04/10 19:26:02 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

static int	ft_isstrdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
	}
	return (0);
}

static void	ft_checkargs(t_cmds *cmds, t_data *data, int cmd_n)
{
	if (!cmds->proccess[2])
	{
		while (cmds->proccess[1])
		{
			if (!ft_isstrdigit(cmds->proccess[1]))
			{
				printf("exit: %s: numeric argument required\n",
					cmds->proccess[1]);
				if (cmd_n != 0)
					return ;
				else
				{
					ft_doublefree(cmds->commands);
					ft_doublefree(cmds->proccess);
					ft_doublefree(data->env);
					ft_doublefree(data->path);
					exit(0);
				}
			}
			else
				exit (ft_atoi(cmds->proccess[1]));
		}
	}
	else
	{
		write(1, "exit: too many arguments\n", 25);
		data->last_out = 1;
	}
}

void	ft_exit(t_cmds *cmds, t_data *data, int cmd_n)
{
	if (!cmds->proccess[1])
	{
		if (cmd_n != 0)
			return ;
		write(1, "exit\n", 5);
		ft_doublefree(cmds->commands);
		ft_doublefree(cmds->proccess);
		ft_doublefree(data->env);
		ft_doublefree(data->path);
		exit(0);
	}
	else
		ft_checkargs(cmds, data, cmd_n);
}
