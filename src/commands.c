/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:36:57 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/10 16:10:45 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

void	ft_commands_n(char *str, t_cmds *Cmds)
{
	int	i;

	i = -1;
	Cmds->n_cmds = 1;
	while (str[++i])
	{
		if (str[i] == '|')
			Cmds->n_cmds++;
	}
}
////////////////////////////////////////////////////////////////

char	**ft_iscommand(t_cmds *Cmds, int i, int j)
{
	char	**new_cmds;
	int		y;
	int		x;

	new_cmds = NULL;
	y = 0;
	while (Cmds->commands[y])
		y++;
	new_cmds = (char **)malloc(sizeof(char *) * (y + 2));
	y = -1;
	while (++y < i)
		new_cmds[y] = ft_strdup(Cmds->commands[y]);
	//dont find the ) properly, ongoing work
	//new_cmds[y] = ft_substr(Cmds->commands[i], j + 2, ft_strlen(Cmds->commands[i]));
	//printf("res: %s\n", new_cmds[y]);
	while (Cmds->commands[y])
	{
		new_cmds[y] = ft_strdup(Cmds->commands[y]);
		y++;
	}
	new_cmds[y] = 0;
	y = -1;
	while (new_cmds[++y])
		printf("str: %s\n", new_cmds[y]);
	ft_doublefree((void **)Cmds->commands);
	exit (0);
	return (new_cmds);
}

char	**ft_isenv(__attribute__((unused))t_cmds *Cmds,__attribute__((unused)) t_data *Data)
{
	return (NULL);
}

void	ft_check_separators(t_cmds *Cmds, t_data *Data)
{
	int	i;
	int	j;

	i = -1;
	while (Cmds->commands[++i])
	{
		j = -1;
		while (Cmds->commands[i][++j])
		{
			if (Cmds->commands[i][j] == '$')
			{
				if (Cmds->commands[i][j + 1] == '(')
					Cmds->commands = ft_iscommand(Cmds, i, j);
				else if(Cmds->commands[i][j + 1] != ' ')
					Cmds->commands = ft_isenv(Cmds, Data);
			}
		}
	}
}

void	ft_minishell_split(t_cmds *Cmds, t_data *Data, char *prompt)
{
	int		i;
	int		pipes;
	int		dollar;
	//int		quotes; //this split is aimed to get the 3 separators/special characters

	i = -1;
	pipes = 0;
	dollar = 0;
	while (prompt[++i])
	{
		if (prompt[i] == '|')
			pipes = 1;
		if (prompt[i] == '$')
			dollar = 1;
	}
	if (pipes)
	{
		Cmds->commands = ft_split(prompt, '|');
		if (dollar == 1)
			ft_check_separators(Cmds, Data);
	}
	else if (!pipes)
	{
		Cmds->commands = (char **)malloc(sizeof(char *) * 2);
		Cmds->commands[0] = ft_strtrim(prompt, " ");
		Cmds->commands[1] = NULL;
		if (dollar == 1)
			ft_check_separators(Cmds, Data);
	}
}

void	ft_fill_commands(char *str, t_cmds *Cmds, t_data *Data)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	ft_minishell_split(Cmds, Data, str);
	exit(0);
	while (str[++i])
	{
		if (str[i] == '|')
			check = 1;
	}
	i = -1;
	if (check == 1)
	{
		Cmds->commands = ft_split(str, '|');
		while (Cmds->commands[++i])
			Cmds->commands[i] = ft_strtrim(Cmds->commands[i], " ");
	}
	else
	{
		Cmds->commands = (char **)malloc(sizeof(char *) * 2);
		Cmds->commands[0] = ft_strdup(str);
		Cmds->commands[1] = NULL;
	}
}

char	*ft_new_value(char	*value,__attribute__((unused)) t_data *Data)
{
	int		i;
	char	*new_value;

	i = -1;
	while (Data->env[++i])
	{
		if (!ft_strncmp(Data->env[i], value, ft_strlen(value)))
		{
			new_value = ft_strdup(Data->env[i]);
			free(value);
			return(new_value);
		}
	}
	return (NULL);
}

void	ft_check_dollars(t_cmds *Cmds, t_data *Data)
{
	int		i;
	int		j;
	char	*value;

	i = -1;
	while (Cmds->commands[++i])
	{
		j = -1;
		while (Cmds->commands[i][++j])
		{
			if (Cmds->commands[i][j] == '$')
			{
				value = ft_substr(Cmds->commands[i], (j + 1), ft_strlen(Cmds->commands[i]));
				value = ft_new_value(value, Data);
			}
		}
	}
}

void	ft_commands(char *str, t_cmds *Cmds, t_data *Data)
{
	if (!str)
		return ;
	ft_commands_n(str, Cmds);
	ft_fill_commands(str, Cmds, Data);
	ft_check_dollars(Cmds, Data);
	ft_init_exec(Cmds, Data);
}
