/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:08:50 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/17 04:09:09by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void ft_pipes_multicommand(t_cmds *cmds, char **split)
{
    char    **tmp;
    int     i;
    int     x;

    if (ft_doublestrlen(split) == 1)
    {
        ft_doublefree(split);
        return ;
    }
    tmp = ft_doublestrdup(cmds->tokens);
    cmds->tokens = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) + ft_doublestrlen(split)));
    i = -1;
    while (++i < (ft_doublestrlen(tmp) - 2))
        cmds->tokens[i] = ft_strdup(tmp[i]);
    x = 0;
    while (split[x])
        cmds->tokens[i++] = ft_strdup(split[x++]);
    cmds->tokens[i] = ft_strdup("|");
    cmds->tokens[i + 1] = 0;
    ft_doublefree(split);
    ft_doublefree(tmp);
}

static void ft_pipes_prev(t_cmds *cmds, char **tmp, int result)
{
    int     i;
    char    *tmp2;

    i = -1;
    cmds->tokens = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) * (ft_doublestrlen(tmp) + 3)));
    while (tmp[++i])
        cmds->tokens[i] = ft_strdup(tmp[i]);
    tmp2 = ft_substr(cmds->prompt, 0, (result - 1));
    cmds->tokens[i] = ft_strtrim(tmp2, " ");
    cmds->tokens[i + 1] = ft_strdup("|");
    cmds->tokens[i + 2] = 0;
    ft_pipes_multicommand(cmds, ft_split(cmds->tokens[i], ' '));
    free(tmp2);
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
    free(tmp2);
    return (result);
}