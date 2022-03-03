/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:38:08 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/03 20:06:09 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_export(__attribute__((unused)) t_data *Data, __attribute__((unused)) t_cmds *Cmds)
{
	printf("LLEGO\n");
	return ;
}

void	ft_check_export(__attribute__((unused))t_data *Data, __attribute__((unused)) t_cmds *Cmds)
{
	int	i;

	if (!Cmds->p_command[1])
	{
		i = -1;
		while (Data->env[++i])
			printf("declare -x %s\n", Data->env[i]);
		exit (0);
	}
	i = -1;
	while (Cmds->p_command[1][++i])
	{
		if (Cmds->p_command[1][i] == '=')
		{
			if (!Cmds->p_command[1][i + 1])
				break ;
			ft_export(Data, Cmds);
		}
	}
	exit (0);
}
