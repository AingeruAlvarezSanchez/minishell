/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:36:57 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/29 10:12:07 by aalvarez         ###   ########.fr       */
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

void	ft_check_separators(t_cmds *Cmds, t_data *Data)
{
	int		j;

	j = -1;
	while (Cmds->commands[0][++j])
	{
		if (Cmds->commands[0][j] == '|')
			Cmds->pipes = 1;
		else if (Cmds->commands[0][j] == '$')
			Cmds->dollar = 1;
		/*else if (Cmds->commands[i][j] == '"' || str[i] == '\'')
			Cmds->quotes = 1;*/
	}
	if (Cmds->pipes == 1)
		Cmds->commands = ft_split(Cmds->commands[0], '|');
	if (Cmds->dollar == 1)
		ft_split_dollar(Cmds, Data);
	/*else if (Cmds->quotes == 1)
		ft_split_quotes();*/
}

void	ft_fill_cmds(char *str, t_cmds *Cmds, t_data *Data)
{
	int	i;

	i = -1;
	Cmds->commands = (char **)malloc(sizeof(char *) * 2);
	Cmds->commands[0] = ft_strdup(str); //This line still gives leaks, probably we need to create tmps every time we malloc new mem for commands
	Cmds->commands[1] = 0;
	Cmds->pipes = 0;
	Cmds->dollar = 0;
	Cmds->quotes = 0;
	ft_check_separators(Cmds, Data);
	i = -1;
	while (Cmds->commands[++i])
		Cmds->commands[i] = ft_strtrim(Cmds->commands[i], " ");
}

void	ft_commands(char *str, t_cmds *Cmds, t_data *Data)
{
	if (!str)
		return ;
	ft_commands_n(str, Cmds);
	ft_fill_cmds(str, Cmds, Data);
	ft_init_exec(Cmds, Data);
}
