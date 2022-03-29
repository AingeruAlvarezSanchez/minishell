/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:38:47 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/29 09:32:57 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>
#include <dirent.h>

void	ft_env(t_data *Data, t_cmds *Cmds)
{
	int	i;
	int	j;

	i = -1;
	if (Cmds->p_command[1])
	{
		if (!opendir(Cmds->p_command[1]))
		{
			printf("env: %s: No such file or directory\n", Cmds->p_command[1]);
			Data->last_out = 1;
			exit(0);
		}
		else
		{
			printf("env: %s: Permission denied\n", Cmds->p_command[1]);
			exit (0);
		}
	}
	while (Data->env[++i])
	{
		j = -1;
		while (Data->env[i][++j])
			write(1, &Data->env[i][j], 1);
		write(1, "\n", 1);
		Data->last_out = 0;
	}
	exit(0);
}
