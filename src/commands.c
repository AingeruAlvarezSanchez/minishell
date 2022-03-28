/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:36:57 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/28 11:03:15 by aalvarez         ###   ########.fr       */
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

void	ft_split_dollar(t_cmds *Cmds, t_data *Data)
{
}

void	ft_fill_cmds(char *str, t_cmds *Cmds, __attribute__((unused)) t_data *Data)
{
	int	i;
	int	pipes;
	int	dollar;
	int	quotes;

	i = -1;
	pipes = 0;
	dollar = 0;
	quotes = 0;
	while (str[++i])
	{
		if (str[i] == '|')
			pipes = 1;
		else if (str[i] == '$')
			dollar = 1;
		/*else if (str[i] == '"' || str[i] == '\'')
			quotes = 1;*/
	}
	if (pipes == 1)
	{
		Cmds->commands = ft_split(str, '|');
		i = -1;
		while (Cmds->commands[++i])
			Cmds->commands[i] = ft_strtrim(Cmds->commands[i], " ");
	}
	else if (dollar == 1)
		ft_split_dollar(Cmds, Data);
	/*else if (quotes == 1)
		ft_split_quotes();*/
}

void	ft_commands(char *str, t_cmds *Cmds, t_data *Data)
{
	if (!str)
		return ;
	ft_commands_n(str, Cmds);
	ft_fill_cmds(str, Cmds, Data);
	exit(0);
	//ft_fill_commands(str, Cmds);
	ft_init_exec(Cmds, Data);
}
