/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:39:08 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/29 00:16:41 by aalvarez         ###   ########.fr       */
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
	while (Cmds->p_command[++i])
	{
		j = -1;
		while (Cmds->p_command[i][++j])
			write(1, &Cmds->p_command[i][j], 1);
		if (Cmds->p_command[i + 1])
			write(1, " ", 1);
	}
	if (flag)
		exit(0);
	write(1, "\n", 1);
	exit(0);
}

void	ft_check_echo(t_cmds *Cmds, t_data *Data)
{
	if (!Cmds->p_command[1])
	{
		write(1, "\n", 1);
		Data->last_out = 0;
		exit (0);
	}
	else
	{
		if (!ft_strncmp(Cmds->p_command[1], "-n", 2))
			ft_echo(Cmds, Cmds->p_command[1]);
		else
			ft_echo(Cmds, NULL);
		Data->last_out = 0;
	}
}
