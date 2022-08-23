/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:09:14 by ecorreia          #+#    #+#             */
/*   Updated: 2022/08/22 11:10:13 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_echo(t_cmds *Cmds, char *flag)
{
	int	i;
	int	j;

	i = 0;
	if (flag)
		i = 1;
	while (Cmds->command[0][++i])
	{
		j = -1;
		while (Cmds->command[0][i][++j])
			write(1, &Cmds->command[0][i][j], 1);
		if (Cmds->command[0][i + 1])
			write(1, " ", 1);
	}
	if (flag)
		exit(0);
	write(1, "\n", 1);
	exit(0);
}

void	ft_check_echo(t_cmds *Cmds)
{
	if (!Cmds->command[0][1])
	{
		write(1, "\n", 1);
		exit (0);
	}
	else
	{
		if (!ft_strncmp(Cmds->command[0][1], "-n", 2))
			ft_echo(Cmds, Cmds->command[0][1]);
		else
			ft_echo(Cmds, NULL);
	}
}