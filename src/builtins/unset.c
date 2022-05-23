/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 08:42:17 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/19 18:34:54 by ecorreia         ###   ########.fr       */
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

void	ft_unset(t_data *data, char **command, int i)
{
	char	*find;
	size_t	len;
	int		j;

	find = command[i];
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

void	ft_unset_error(char **command, t_data *data, int i)
{
	printf("unset: '%s': not a valid identifier\n",
		command[i]);
	data->last_out = 1;
}

void	ft_check_unset(char **command, t_data *data, int cmd_n)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	check = 1;
	while (command[++i])
	{
		j = -1;
		while (command[i][++j])
		{
			if (command[i][j] == '=')
			{
				ft_unset_error(command, data, i);
				check = 0;
			}
		}
		if (check == 1)
		{
			if (cmd_n != 0)
				return ;
			ft_unset(data, command, i);
		}
		check = 1;
	}
}