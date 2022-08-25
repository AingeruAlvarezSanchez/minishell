/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 08:40:53 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/21 06:24:59 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

char	*ft_create_value(char **command, int x, int i)
{
	char	*value;
	//int		size;
	//int		ref;

	//size = 0;
	//ref = x;
	if (command[i][x])
	{
		x = x - 1;
		value = ft_strdup(command[i]);
		/*while (command[i][++x])
			size++;
		value = (char *)malloc(sizeof(char) * (size + 1));
		x = 0;
		while (command[i][ref])
			value[x++] = command[i][ref++];
		value[x] = 0;*/
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
    (void)  find;

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
		tmp[i] = ft_strdup(value);
		tmp[i + 1] = 0;
	}
	return (tmp);
}

void	ft_export(t_data *data, char **command, int i, int j)
{
	int		x;
	char	*find;
	char	*value;

	find = (char *)malloc(sizeof(char) * (j + 2));
	x = -1;
	while (++x <= j)
		find[x] = command[i][x];
	find[x] = 0;
	value = ft_create_value(command, x, i);
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

int sizeOf2Array(char **array)
{
	int i;

	if(!array)
		return 0;
	i = 0;
	while (array[i])
		i++;
	return (i);
}
/*
void ftUninitexport(t_data *data, char* command)
{
	char** tmp;
	int i;

    tmp = (char **)malloc(sizeof(char *) * sizeOf2Array(data->export_env) + 2);
    int j = sizeof(char *) * sizeOf2Array(data->export_env) + 2;
    printf("%d", j);
	i = -1;
	while(data->export_env[++i])
	{
		tmp[i] = ft_strdup(data->export_env[i]);
	}
	ft_doublefree(data->export_env);

    tmp[i] = ft_strdup(command);

	tmp[i + 1] = 0;

	while(tmp[++i])
	{
		data->export_env[i] = ft_strdup(tmp[i]);
	}
    data->export_env[i + 1] = 0;
	//data->export_env = ft_doublestrdup(tmp);
	free(tmp);
}*/

void	ftUninitexport(t_data *data, char *value)
{
	int		i;
	char	**tmp;

	i = 0;
	while (data->export_env[i])
		i++;
	//tmp = (char **)malloc(sizeof(char *) * sizeOf2Array(data->export_env) + 2);
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (data->export_env[++i])
	    tmp[i] = ft_strdup(data->export_env[i]);
	ft_doublefree(data->export_env);
	tmp[i] = ft_strdup(value);
	tmp[i + 1] = 0;
	while(tmp[++i])
		data->export_env[i] = ft_strdup(tmp[i]);
	data->export_env[i] = 0;
	free(tmp);
}

void	ft_check_export(char **command, t_data *data, int cmd_n)
{
	int	i;
	int	j;

	if (!command[1])
	{
		i = -1;
		while (data->export_env[++i])
			printf("declare -x %s\n", data->export_env[i]);
		data->last_out = 0;
	}
	i = -1;
	while (command[++i])
	{
		j = -1;
		while (command[i][++j])
		{
			if (command[i][j] == '=')
			{
				if (cmd_n != 0)
					return ;
				ft_export(data, command, i, j);
				break ;
			}
			else if (command[i][j + 1] == 0 && command[i] != command[0])
				ftUninitexport(data, command[i]);
		}
	}
	data->last_out = 0;
}
