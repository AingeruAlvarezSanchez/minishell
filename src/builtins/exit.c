/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:12:34 by ecorreia          #+#    #+#             */
/*   Updated: 2022/09/16 21:12:38 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param cmds struct with commands
 * @param n_cmds command position
 * @param pos_cmd number of commands
 */
static void	ft_exit_with_arg(t_cmds_all *cmds, int n_cmds, int pos_cmd)
{
	int	c;

    c = 0;
	while (cmds->cmds[n_cmds].cmd[1][c])
	{
		if (ft_isalpha(cmds->cmds[n_cmds].cmd[1][c]))
		{
			printf("Ejemplo₺ : %s %s\n",
                   cmds->cmds[n_cmds].cmd[1],
                   ": numeric argument required");
			g_exit_status = 1;
			if (pos_cmd == 1)
			{
				ft_free_commands(cmds);
				exit(255);
			}
		}
		c++;
	}
	g_exit_status = ft_atoi(cmds->cmds[n_cmds].cmd[1]);
	if (pos_cmd == 1)
		exit(ft_atoi(cmds->cmds[n_cmds].cmd[1]));
}

/**
 *
 * @param cmds struct with commands
 * @param pos_cmd command position
 * @param n_cmds number of commands
 * @return
 */
int	ft_exit(t_cmds_all *cmds, int pos_cmd, int n_cmds)
{
	int	pos;

	if (pos_cmd != n_cmds - 1)
		return (1);
	if (n_cmds == 1)
		write(1, "exit\n", 5);
    pos = 0;
	while (cmds->cmds[pos_cmd].cmd[pos])
		pos++;
	if (pos > 2)
	{
		printf("Ejemplo₺ : Too many arguments\n");
		g_exit_status = 1;
		return (0);
	}
	if (cmds->cmds[pos_cmd].cmd[1])
        ft_exit_with_arg(cmds, pos_cmd, n_cmds);
	if (n_cmds == 1)
	{
		ft_free_commands(cmds);
		g_exit_status = 0;
		exit(0);
	}
	return (0);
}
