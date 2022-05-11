/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 08:42:17 by aalvarez          #+#    #+#             */
/*   Updated: 2022/04/07 17:24:36 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

char	**ft_unset_env(t_data *data, int j)
{
	char	**new;
	int		i;
	int		x;

	i = 0;
	while (data->env[i])
		i++;
	new = (char **)malloc(sizeof(char *) * i);
	i = -1;
	x = 0;
	while (data->env[++i])
	{
		if (i == j)
			i++;
		if (!data->env[i])
			break ;
		new[x++] = ft_strdup(data->env[i]);
	}
	new[x] = 0;
	ft_doublefree(data->env);
	return (new);
}

void	ft_unset(t_data *data, t_cmds *cmds, int i)
{
	char	*find;
	size_t	len;
	int		j;

	find = cmds->proccess[i];
	len = ft_strlen(find);
	j = -1;
	while (data->env[++j])
	{
		if (!ft_strncmp(data->env[j], find, len))
		{
			data->env = ft_unset_env(data, j);
			data->last_out = 0;
			break ;
		}
	}
}

void	ft_unset_error(t_cmds *cmds, t_data *data, int i)
{
	printf("unset: '%s': not a valid identifier\n",
		cmds->proccess[i]);
	data->last_out = 1;
}

void	ft_check_unset(t_cmds *cmds, t_data *data, int cmd_n)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	check = 1;
	while (cmds->proccess[++i])
	{
		j = -1;
		while (cmds->proccess[i][++j])
		{
			if (cmds->proccess[i][j] == '=')
			{
				ft_unset_error(cmds, data, i);
				check = 0;
			}
		}
		if (check == 1)
		{
			if (cmd_n != 0)
				return ;
			ft_unset(data, cmds, i);
		}
		check = 1;
	}
}
