/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 04:23:58 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/04 19:41:31 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

static void    ft_firstcasepipe(t_cmds *cmds, int jref)
{
    char    **tmp;
    char    *tmp2;

    tmp = (char **)malloc(sizeof(char *) * 4);
    tmp2 = ft_substr(cmds->tokens[0], 0, jref);
    tmp[0] = ft_strtrim(tmp2, " ");
    free(tmp2);
    tmp[1] = ft_strdup("|");
    tmp2 = ft_substr(cmds->tokens[0], (jref + 1), (ft_strlen(cmds->tokens[0]) - (jref - 1)));
    tmp[2] = ft_strtrim(tmp2, " ");
    free(tmp2);
    tmp[3] = 0;
    ft_doublefree(cmds->tokens);
    ft_newcmds(cmds, tmp);
    ft_doublefree(tmp);
}

static void    ft_pipes(t_cmds *cmds, int iref, int jref)
{
    int     i;
    char    **tmp;
    char    *tmp2;

    i = -1;
    tmp = (char **)malloc(sizeof(char *) * (ft_doublestrlen(cmds->tokens) + 4));
    while (++i < iref)
        tmp[i] = ft_strdup(cmds->tokens[i]);
    tmp2 = ft_substr(cmds->tokens[i], 0, jref);
    tmp[i] = ft_strtrim(tmp2, " ");
    free(tmp2);
    tmp[i + 1] = ft_strdup("|");
    tmp2 = ft_substr(cmds->tokens[i], (jref + 1), (ft_strlen(cmds->tokens[i]) - (jref - 1)));
    tmp[i + 2] = ft_strtrim(tmp2, " ");
    free(tmp2);
    tmp[i + 3] = 0;
    ft_doublefree(cmds->tokens);
    ft_newcmds(cmds, tmp);
}

int ft_check_pipes(t_cmds *cmds, int iref, int jref)
{
	if (ft_pipes_error(cmds, iref, jref))
		return (1);
    if (ft_doublestrlen(cmds->tokens) == 1)
    {
        ft_firstcasepipe(cmds, jref);
        return (0);
    }
    ft_pipes(cmds, iref, jref);
    return (0);
}
