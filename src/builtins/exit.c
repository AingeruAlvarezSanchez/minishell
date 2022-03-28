/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:38:39 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/28 23:13:38 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>
#include <unistd.h>

static int	ft_isstrdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < 0 || str[i] > 9)
			return (1);
	}
	return (0);
}

static void	ft_checkargs(t_cmds *Cmds, int cmd_pos)
{
	if (!Cmds->p_command[2])
	{
		while (Cmds->p_command[1])
		{
			if (!ft_isstrdigit(Cmds->p_command[1]))
			{
				printf("chain is: %s\n", Cmds->p_command[1]);
				printf("exit: %s: numeric argument required\n",
					Cmds->p_command[1]);
				if (cmd_pos != 0)
					return ;
				else
					exit(0);
			}
			else
				exit (ft_atoi(Cmds->p_command[1]));
		}
	}
	else
		write(1, "exit: too many arguments\n", 25);
}

void	ft_exit(t_cmds *Cmds, int cmd_pos)
{
	if (!Cmds->p_command[1])
	{
		if (cmd_pos != 0)
			return ;
		write(1, "exit\n", 5);
		exit(0);
	}
	else
		ft_checkargs(Cmds, cmd_pos);
}
