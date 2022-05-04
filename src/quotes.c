/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 01:48:36 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/04 03:04:36by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

static void ft_firsttoken(t_cmds *cmds, char **tmp)
{
    int i;
    int j;

    i = -1;
    while (tmp[++i])
    {
        if (tmp[i][0])
            j++;
    }
    cmds->tokens = (char **)malloc(sizeof(char *) * (j + 1));
    i = -1;
    j = 0;
    while (tmp[++i])
    {
        if (tmp[i][0])
            cmds->tokens[j++] = ft_strdup(tmp[i]);
    }
    cmds->tokens[j] = 0;
    ft_doublefree(tmp);
}

static void ft_firstcasequote(t_cmds *cmds, int iref, int jref, int xref)
{
    char    **tmp;
    char    *tmp2;

    if (cmds->tokens[iref][xref + 1])
        tmp = (char **)malloc(sizeof(char *) * 4);
    else
        tmp = (char **)malloc(sizeof(char *) * 3);
    tmp[0] = ft_substr(cmds->tokens[0], 0, jref);
    tmp2 = ft_substr(cmds->tokens[0], jref, ((xref + 1) - jref));
    tmp[1] = ft_strtrim(tmp2, " ");
    free(tmp2);
    if (cmds->tokens[iref][xref + 1])
    {
        tmp2 = ft_substr(cmds->tokens[0], (xref + 1), ft_strlen(cmds->tokens[0]) - (xref + 1));
        tmp[2] = ft_strtrim(tmp2, " ");
        free(tmp2);
        tmp[3] = 0;
    }
    else
        tmp[2] = 0;
    ft_doublefree(cmds->tokens);
    ft_firsttoken(cmds, tmp);
}

static char	**ft_nofinal(t_cmds *cmds, int iref, int jref, int xref)
{
	int		i;
    char    **tmp;
    char    *tmp2;

    tmp = (char **)malloc(sizeof(char *) * (ft_doublestrlen(cmds->tokens) + 2));
    i = -1;
    while (++i < iref)
        tmp[i] = ft_strdup(cmds->tokens[i]);
    tmp2 = ft_substr(cmds->tokens[i], 0, jref);
    tmp[i] = ft_strtrim(tmp2, " ");
    free(tmp2);
    tmp2 = ft_substr(cmds->tokens[i], jref, ((xref + 1) - jref));
    tmp[i + 1] = ft_strtrim(tmp2, " ");
    free(tmp2);
    tmp[i + 2] = 0;
	ft_doublefree(cmds->tokens);
	return (tmp);
}

static char	**ft_full_final(t_cmds *cmds, int iref, int jref, int xref)
{
    int     i;
    char    **tmp;
    char    *tmp2;

    tmp = (char **)malloc(sizeof(char *) * (ft_doublestrlen(cmds->tokens) + 3));
    i = -1;
    while (++i < iref)
        tmp[i] = ft_strdup(cmds->tokens[i]);
    tmp2 = ft_substr(cmds->tokens[i], 0, jref);
    tmp[i] = ft_strtrim(tmp2, " ");
    free(tmp2);
    tmp2 = ft_substr(cmds->tokens[i], jref, ((xref + 1) - jref));
    tmp[i + 1] = ft_strtrim(tmp2, " ");
    free(tmp2);
    tmp2 = ft_substr(cmds->tokens[iref], (xref + 1), (ft_strlen(cmds->tokens[iref]) - (xref - 1)));
    tmp[i + 2] = ft_strtrim(tmp2, " ");
    free(tmp2);
    tmp[i + 3] = 0;
	ft_doublefree(cmds->tokens);
    return (tmp);
}

void    ft_quotes(t_cmds *cmds, int iref, int jref, int xref)
{
    char    **tmp;

    if (ft_doublestrlen(cmds->tokens) == 1)
    {
        ft_firstcasequote(cmds, iref, jref, xref);
        return ;
    }
    if (cmds->tokens[iref][xref + 1])
		tmp = ft_full_final(cmds, iref, jref, xref);
    else
		tmp = ft_nofinal(cmds, iref, jref, xref);
    ft_newcmds(cmds, tmp);
    ft_doublefree(tmp);
}
