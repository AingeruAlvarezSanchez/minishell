/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:03:58 by aalvarez          #+#    #+#             */
/*   Updated: 2022/03/29 00:17:40 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

char	**ft_unset_env(t_data *Data, int j)
{
	char	**new;
	int		i;
	int		x;

	i = 0;
	while (Data->env[i])
		i++;
	new = (char **)malloc(sizeof(char *) * i);
	i = -1;
	x = 0;
	while (Data->env[++i])
	{
		if (i == j)
			i++;
		if (!Data->env[i])
			break ;
		new[x++] = ft_strdup(Data->env[i]);
	}
	new[x] = 0;
	ft_doublefree(Data->env);
	return (new);
}

void	ft_unset(t_data *Data, t_cmds *Cmds, int i)
{
	char	*find;
	size_t	len;
	int		j;

	find = Cmds->p_command[i];
	len = ft_strlen(find);
	j = -1;
	while (Data->env[++j])
	{
		if (!ft_strncmp(Data->env[j], find, len))
		{
			Data->env = ft_unset_env(Data, j);
			Data->last_out = 0;
			break ;
		}
	}
}

void	ft_unset_error(t_cmds *Cmds, t_data *Data, int i)
{
	printf("unset: '%s': not a valid identifier\n",
		Cmds->p_command[i]);
	Data->last_out = 1;
}

void	ft_check_unset(t_data *Data, t_cmds *Cmds, int cmd_pos)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	check = 1;
	while (Cmds->p_command[++i])
	{
		j = -1;
		while (Cmds->p_command[i][++j])
		{
			if (Cmds->p_command[i][j] == '=')
			{
				ft_unset_error(Cmds, Data, i);
				check = 0;
			}
		}
		if (check == 1)
		{
			if (cmd_pos != 0)
				return ;
			ft_unset(Data, Cmds, i);
		}
		check = 1;
	}
}
