/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:10:04 by aalvarez          #+#    #+#             */
/*   Updated: 2022/02/20 16:14:51by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <string.h>
#include "libft/libft.h"

void	ft_initialize_data(t_data *Data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (ft_strncmp(Data->env[i], "PATH=", 5))
		i++;
	Data->path = ft_split(Data->env[i], ':');
	i = -1;
	while (Data->path[++i])
	{
		tmp = ft_strjoin(Data->path[i], "/");
		free(Data->path[i]);
		Data->path[i] = tmp;
	}
	i = 0;
}

void	ft_commands_n(char *str, t_cmds *cmds)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	cmds->n_cmds = 0;
	while (str[i])
	{
		if (str[i] == '-')
		{
			while (str[i] != ' ' && str[i])
				i++;	
		}
		if (ft_isalpha(str[i]))
		{
			cmds->n_cmds += 1;
			while (str[i] != ' ' && str[i])
				i++;
		}
		i++;
	}
}

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv, char **envp)
{
	char	*str;
	t_data	data;
	t_cmds	cmds;

	data.env = envp;
	ft_initialize_data(&data);
	while (1)
	{
		str = readline("ejemplo1 ₺ ");
		add_history(str);
		ft_commands_n(str, &cmds);
		free(str);
	}
	return (0);
}
