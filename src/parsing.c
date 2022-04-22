/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 04:27:25 by aalvarez          #+#    #+#             */
/*   Updated: 2022/04/22 16:40:49 by aalvarez         ###   ########.fr       */
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
 * @param cmd_i the command number on wich the create 
 * command is called
 */
void	ft_create_command(t_cmds *cmds,__attribute__((unused)) int iref,__attribute__((unused)) int cmd_i)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = ft_strjoin(" ", cmds->tokens[i]);
	while (++i < iref)
	{
		tmp2 = ft_strjoin(tmp, cmds->tokens[i]);
		free(tmp);
		tmp = ft_strdup(tmp2);
		free(tmp2);
	}
	cmds->commands[cmd_i] = ft_strtrim(tmp, " ");
	free(tmp);
	tmp = ft_strjoin(" ", cmds->tokens[++i]);
	while (cmds->tokens[++i])
	{
		tmp2 = ft_strjoin(tmp, cmds->tokens[i]);
		free(tmp);
		tmp = ft_strdup(tmp2);
		free(tmp2);
	}
	cmds->commands[cmd_i + 1] = ft_strtrim(tmp, " ");
	cmds->commands[cmd_i + 2] = 0;
}

void	ft_revsubstr(t_cmds *cmds, int iref, char c)
{
	int		i;
	char	*tmp;

	i = ft_strlen(cmds->commands[iref]);
	while (cmds->commands[iref][i] != c)
		i--;
	tmp = ft_substr(cmds->commands[iref], (i + 1), (ft_strlen(cmds->commands[iref]) - (i + 1)));
	free(cmds->commands[iref]);
	cmds->commands[iref] = ft_strtrim(tmp, " ");
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
	cmds->commands = (char **)malloc(sizeof(char *) * ((cmds->n_cmds) + 1));
	while (cmds->tokens[++i])
	{
		j = -1;
		while (cmds->tokens[i][++j])
		{
			if (cmds->tokens[i][0] == '|')
				ft_create_command(cmds, i, cmd_i++);
		}
	}
	if (cmds->n_cmds > 2)
	{
		i = -1;
		while (cmds->commands[++i])
		{
			j = -1;
			while (cmds->commands[i][++j])
			{
				if (cmds->commands[i][j] == '|')
				{
					ft_revsubstr(cmds, i, '|');
					break ;
				}
			}
		}
	}
}

/**
 * @brief When there is only one command, this function
 * creates a 2 spaces double array and allocates the 
 * prompt and a NULL spot
 */
void	ft_mono_command(t_cmds *cmds)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	cmds->commands = (char **)malloc(sizeof(char *) * 2);
	i = 0;
	tmp = ft_strjoin(" ", cmds->tokens[0]);
	while (cmds->tokens[++i])
	{
		tmp2 = ft_strjoin(tmp, cmds->tokens[i]);
		free(tmp);
		tmp = ft_strdup(tmp2);
		free(tmp2);
	}
	tmp2 = ft_strtrim(tmp, " ");
	cmds->commands[0] = ft_strdup(tmp2);
	free(tmp);
	free(tmp2);
	cmds->commands[1] = 0;
}
