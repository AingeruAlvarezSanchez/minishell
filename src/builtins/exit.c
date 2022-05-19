/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 06:40:11 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/11 10:18:35 by ecorreia         ###   ########.fr       */
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
/*
void	ft_free(t_cmds *cmds, t_data *data)
{
	ft_doublefree(cmds->commands);
	ft_doublefree(cmds->proccess);
	ft_doublefree(data->env);
	ft_doublefree(data->path);
}
*/
static void	ft_checkargs(char *flag, t_data *data, int cmd_n)
{
	(void) data;
	//if (!cmds->proccess[2])
	//{
		while (flag)
		{
			if (!ft_isstrdigit(flag))
			{
				printf("exit: %s: numeric argument required\n", flag);
				if (cmd_n != 0)
					return ;
				else
				{
					//ft_free(cmds, data);
					exit(0);
				}
			}
			else
				exit (ft_atoi(flag));
		}
	//}
	//else
	//{
	//	write(1, "exit: too many arguments\n", 25);
	//	data->last_out = 1;
	//}
}

void	ft_exit(char *flag, t_data *data, int cmd_n)
{
	if (!flag)
	{
		if (cmd_n != 0)
			return ;
		write(1, "exit\n", 5);
		//ft_free(cmds, data);
		exit(0);
	}
	else
		ft_checkargs(flag, data, cmd_n);
}
