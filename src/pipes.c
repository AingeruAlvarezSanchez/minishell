/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:08:50 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/16 18:09:24 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void ft_pipes_prev(t_cmds *cmds, char **tmp, int result)
{
    int i;

    i = -1;
    cmds->tokens = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) * (ft_doublestrlen(tmp) + 3)));
    while (tmp[++i])
        cmds->tokens[i] = ft_strdup(tmp[i]);
    cmds->tokens[i] = ft_substr(cmds->prompt, 0, (result - 1));
    cmds->tokens[i + 1] = ft_strdup("|");
    cmds->tokens[i + 2] = 0;
}

int ft_pipes(t_cmds *cmds, int xref)
{
    int     result;
    int     i;
    char    **tmp;
    char    *tmp2;

    result = xref;
    while (cmds->prompt[result] == '|')
        result++;
    tmp = ft_doublestrdup(cmds->tokens);
    tmp2 = ft_substr(cmds->prompt, 0, xref);
    if (tmp2[0] && tmp2[0] != '|')
        ft_pipes_prev(cmds, tmp, result);
    else
    {
        i = -1;
        cmds->tokens = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) * (ft_doublestrlen(tmp) + 2)));
        while (tmp[++i])
            cmds->tokens[i] = ft_strdup(tmp[i]);
        cmds->tokens[i] = ft_strdup("|");
        cmds->tokens[i + 1] = 0;
    }
    ft_doublefree(tmp);
    return (result);
}