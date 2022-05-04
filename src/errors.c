/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 23:40:23 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/04 05:08:01 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

void    ft_nonulls(t_cmds *cmds)
{
    int     i;
    int     j;
    char    **tmp;

    j = 0;
    i = -1;
    while (cmds->tokens[++i])
    {
        if (cmds->tokens[i][0])
            j++;
    }
    tmp = (char **)malloc(sizeof(char *) * (j + 1));
    i = -1;
    j = 0;
    while (cmds->tokens[++i])
    {
        if (cmds->tokens[i][0])
            tmp[j++] = ft_strdup(cmds->tokens[i]);
    }
    tmp[j] = 0;
    ft_doublefree(cmds->tokens);
    ft_newcmds(cmds, tmp);
    ft_doublefree(tmp);
}

int	ft_nomorecommand(t_cmds *cmds, int iref, int jref)
{
	while (cmds->tokens[iref][jref++])
	{
		if (cmds->tokens[iref][jref] > 32)
			return (0);
	}
	return (1);
}

int  ft_pipes_error(t_cmds *cmds, int iref, int jref)
{
	if (!cmds->tokens[iref][jref + 1] || ft_nomorecommand(cmds, iref, jref))
	{
		printf("Syntax error near unexpected token '|'\n");
		return (1);
	}
    else if (cmds->tokens[iref][jref + 1] == '|')
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

int  ft_has_final(t_cmds *cmds, int iref, int jref, int c)
{
    int x;

    x = jref;
    while (cmds->tokens[iref][jref++])
    {
        x++;
        if (cmds->tokens[iref][jref] == c)
            return (x);
    }
    printf("syntax error, one ore more quotes are not closed\n");
    return (-1);
}
