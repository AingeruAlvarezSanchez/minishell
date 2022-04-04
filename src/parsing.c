/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 04:27:25 by aalvarez          #+#    #+#             */
/*   Updated: 2022/04/04 04:25:33 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

/**
 * @brief This function creates a new double array containing
 * the commands already separated by pipes
 * 
 * @param iref reference to the i axis on cmds->tokens
 * at moment of finding an readable pipe character
 * @param cmd_i 
 */
void	ft_create_command(t_cmds *cmds, int iref, int cmd_i)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strdup(" ");
	while (++i < iref)
		tmp = ft_strjoin(tmp, cmds->tokens[i]);
	i = -1;
	while (tmp[++i])
	{
		if (tmp[i] == '|')
		{
			tmp = ft_substr(tmp, (i + 1), ft_strlen(tmp));
			i = -1;
		}
	}
	cmds->commands[cmd_i] = ft_strdup(tmp);
	free(tmp);
	tmp = ft_strdup(" ");
	while (cmds->tokens[++iref])
		tmp = ft_strjoin(tmp, cmds->tokens[iref]);
	cmds->commands[cmd_i + 1] = ft_strdup(tmp);
	cmds->commands[cmd_i + 2] = 0;
	free(tmp);
}

/**
 * @brief Once every separator or metacharacter has been
clasified, this function creates the definitive version
of the commands separated by pipes
 */
void	ft_parser(t_cmds *cmds)
{
	int	i;
	int	j;
	int	cmd_i;

	cmd_i = 0;
	i = -1;
	cmds->commands = (char **)malloc(sizeof(char *) * (cmds->n_cmds + 1));
	while (cmds->tokens[++i])
	{
		j = -1;
		while (cmds->tokens[i][++j])
		{
			if (cmds->tokens[i][0] == '|')
			{
				ft_create_command(cmds, i, cmd_i);
				cmd_i++;
			}
		}
	}
	cmds->commands[cmd_i + 1] = 0;
	i = -1;
	while (cmds->commands[++i])
		cmds->commands[i] = ft_strtrim(cmds->commands[i], " ");
}

void	ft_mono_command(t_cmds *cmds)
{
	int		i;
	char	*tmp;

	cmds->commands = (char **)malloc(sizeof(char *) * 2);
	i = -1;
	tmp = ft_strdup(" ");
	while (cmds->tokens[++i])
		tmp = ft_strjoin(tmp, cmds->tokens[i]);
	cmds->commands[0] = ft_strdup(ft_strtrim(tmp, " "));
	free(tmp);
	cmds->commands[1] = 0;
}