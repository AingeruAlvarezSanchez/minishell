/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:28:39 by aalvarez          #+#    #+#             */
/*   Updated: 2022/03/31 21:28:39 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

/* This function checks if the pipe is next to other pipes, making
it an invalid pipe and returning to prompt*/
static int	ft_pipes_error(t_cmds *cmds, int iref, int jref)
{
	if (cmds->tokens[iref][jref + 1] == '|')
	{
		if (jref == 0)
		{
			printf("Syntax error near unexpected token '|'\n");
			return (1);
		}
		else
		{
			if (cmds->tokens[iref][jref + 2] == '|')
			{
				printf("Syntax error near unexpected token '|'\n");
				return (1);
			}
		}
	}
	return (0);
}

/* This function checks for pipes that are not inside quotes and can be 
interpreted and creates a new cmds->tokens array separating the pipe in 
a single line for better treatment after the initial checks */
int	ft_check_pipes(t_cmds *cmds, int iref, int jref)
{
	char	**tmp;
	char	*tmp2;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * (ft_doublestrlen(cmds->tokens) + 3));
	if (ft_pipes_error(cmds, iref, jref))
		return (1);
	tmp2 = ft_substr(cmds->tokens[iref], 0, jref);
	i = -1;
	while (++i < iref)
		tmp[i] = ft_strdup(cmds->tokens[i]);
	tmp[i] = ft_strdup(tmp2);
	free(tmp2);
	tmp2 = ft_substr(cmds->tokens[iref], (jref - 1), 2);
	tmp[i + 1] = ft_strtrim(tmp2, " ");
	tmp[i + 2] = ft_substr(cmds->tokens[iref], (jref + 1), ft_strlen(cmds->tokens[iref]));
	tmp[i + 3] = 0;
	ft_doublefree(cmds->tokens);
	cmds->tokens = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) + 1));
	i = -1;
	while (tmp[++i])
		cmds->tokens[i] = ft_strdup(tmp[i]);
	cmds->tokens[i] = 0;
	ft_doublefree(tmp);
	free(tmp2);
	return (0);
}

