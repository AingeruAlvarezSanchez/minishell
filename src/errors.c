/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:29:19 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/10 23:33:33 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

int  ft_has_final(t_cmds *cmds, int xref, char c)
{
    while (cmds->prompt[++xref])
    {
        if (cmds->prompt[xref] == c)
            return (1);
    }
    printf("Syntax error, one ore more quotes are not closed\n");
    return (0);
}

int  ft_pipes_error(t_cmds *cmds, int xref)
{
    if (!cmds->prompt[xref + 1]/* || ft_nomorecommand(cmds, iref, jref)*/)
	{
		printf("1: Syntax error near unexpected token '|'\n");
		return (1);
	}
    else if (cmds->prompt[xref + 1] == '|')
	{
		if (xref == 0)
		{
			printf("2: Syntax error near unexpected token '|'\n");
			return (1);
		}
		else
		{
			if (cmds->prompt[xref + 2] == '|')
			{
				printf("3: Syntax error near unexpected token '|'\n");
				return (1);
			}
		}
	}
	return (0);
}