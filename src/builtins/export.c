/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 08:40:53 by aalvarez          #+#    #+#             */
/*   Updated: 2022/04/04 08:48:03 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

char	*ft_create_value(t_cmds *cmds, int x, int i)
{
	char	*value;
	int		size;
	int		ref;

	size = 0;
	ref = x;
	if (cmds->proccess[i][x])
	{
		x = x - 1;
		while (cmds->proccess[i][++x])
			size++;
		value = (char *)malloc(sizeof(char) * (size + 1));
		x = 0;
		while (cmds->proccess[i][ref])
			value[x++] = cmds->proccess[i][ref++];
		value[x] = 0;
	}
	else
		return (NULL);
	return (value);
}

void	ft_alreadyenv(t_data *data, char *value, char *find, int x)
{
	if (!value)
	{
		free(data->env[x]);
		data->env[x] = ft_strdup(find);
	}
	else
	{
		free(data->env[x]);
		data->env[x] = ft_strjoin(find, value);
	}
}

char	**ft_newenv(t_data *data, char *value, char *find)
{
	int		i;
	char	**tmp;

	i = 0;
	while (data->env[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (data->env[++i])
		tmp[i] = ft_strdup(data->env[i]);
	ft_doublefree(data->env);
	if (!value)
	{
		tmp[i] = ft_strdup(find);
		tmp[i + 1] = 0;
	}
	else
	{
		tmp[i] = ft_strjoin(find, value);
		tmp[i + 1] = 0;
	}
	return (tmp);
}

void	ft_export(t_data *data, t_cmds *cmds, int i, int j)
{
	int		x;
	char	*find;
	char	*value;

	find = (char *)malloc(sizeof(char) * (j + 2));
	x = -1;
	while (++x <= j)
		find[x] = cmds->proccess[i][x];
	find[x] = 0;
	value = ft_create_value(cmds, x, i);
	x = -1;
	while (data->env[++x])
	{
		if (!ft_strncmp(data->env[x], find, (j + 1)))
		{
			ft_alreadyenv(data, value, find, x);
			free(value);
			free(find);
			return ;
		}
	}
	data->env = ft_newenv(data, value, find);
	data->last_out = 0;
	free(value);
	free(find);
}

void	ft_check_export(t_cmds *cmds, t_data *data, int cmd_n)
{
	int	i;
	int	j;

	if (!cmds->proccess[1])
	{
		i = -1;
		while (data->env[++i])
			printf("declare -x %s\n", data->env[i]);
		data->last_out = 0;
	}
	i = -1;
	while (cmds->proccess[++i])
	{
		j = -1;
		while (cmds->proccess[i][++j])
		{
			if (cmds->proccess[i][j] == '=')
			{
				if (cmd_n != 0)
					return ;
				ft_export(data, cmds, i, j);
			}
		}
	}
	data->last_out = 0;
}