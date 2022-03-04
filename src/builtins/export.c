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

char	*ft_create_value(t_cmds *Cmds, int x, int i)
{
	char	*value;
	int	size;
	int	ref;

	size = 0;
	ref = x;
	if (Cmds->p_command[i][x])
	{
		x = x - 1;
		while (Cmds->p_command[i][++x])
			size++;
		value = (char *)malloc(sizeof(char) * (size + 1));
		x = 0;
		while (Cmds->p_command[i][ref])
			value[x++] = Cmds->p_command[i][ref++];
		value[x] = 0;
	}
	else
		return (NULL);
	return (value);
}

void	ft_alreadyenv(t_data *Data, char *value, char *find, int x)
{
	if (!value)
	{
		free(Data->env[x]);
		Data->env[x] = ft_strdup(find);
	}
	else
	{
		free(Data->env[x]);
		Data->env[x] = ft_strjoin(find, value);
	}
}

void	ft_newenv(__attribute__((unused)) t_data *Data, __attribute__((unused))char *value, __attribute__((unused))char *find)
{
	printf("THE ENV DOESNT EXIST\n");
}

void	ft_export(t_data *Data, t_cmds *Cmds, int i, int j)
{
	int	x;
	char	*find;
	char	*value;

	find = (char *)malloc(sizeof(char) * (j + 2));
	x = -1;
	while (++x <= j)
		find[x] = Cmds->p_command[i][x];
	find[x] = 0;
	value = ft_create_value(Cmds, x, i);
	x = -1;
	while (Data->env[++x])
	{
		if (!ft_strncmp(Data->env[x], find, (j + 1)))
		{
			ft_alreadyenv(Data, value, find, x);
			free(value);
			free(find);
			return ;
		}
	}
	ft_newenv(Data, value, find);
	free(value);
	free(find);
}

void	ft_check_export(t_data *Data, t_cmds *Cmds)
{
	int	i;
	int	j;

	if (!Cmds->p_command[1])
	{
		i = -1;
		while (Data->env[++i])
			printf("declare -x %s\n", Data->env[i]);
		exit (0);
	}
	i = -1;
	while (Cmds->p_command[++i])
	{
		j = -1;
		while (Cmds->p_command[i][++j])
		{
			if (Cmds->p_command[i][j] == '=')
				ft_export(Data, Cmds, i, j);
		}
	}
}

