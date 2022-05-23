/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lastjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:41:26 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/21 05:56:36 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void ft_prevtokens(t_cmds *cmds, char **split)
{
    char    **tmp;
    int     i;
    int     x;

    tmp = ft_doublestrdup(cmds->tokens);
    i = -1;
    cmds->tokens = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) + ft_doublestrlen(split) + 1));
    while (tmp[++i])
        cmds->tokens[i] = ft_strdup(tmp[i]);
    x = 0;
    while (split[x])
        cmds->tokens[i++] = ft_strdup(split[x++]);
    cmds->tokens[i] = 0;
    ft_doublefree(tmp);
}

static int ft_islastmulti(t_cmds *cmds, char **split)
{
    int i;

    if (ft_doublestrlen(split) != 1)
    {
        if (cmds->tokens[0])
            ft_prevtokens(cmds, split);
        else
        {
            i = -1;
            cmds->tokens = (char **)malloc(sizeof(char *) * (ft_doublestrlen(split) + 1));
            while (split[++i])
                cmds->tokens[i] = ft_strdup(split[i]);
            cmds->tokens[i] = 0;
        }
        ft_doublefree(split);
        return (1);
    }
    ft_doublefree(split);
    return (0);
}

void ft_lastjoin(t_cmds *cmds)
{
    char    **tmp;
    int     i;

    i = -1;
    if (ft_islastmulti(cmds, ft_split(cmds->prompt, ' ')))
        return ;
    tmp = ft_doublestrdup(cmds->tokens);
    cmds->tokens = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) + 2));
    while (tmp[++i])
        cmds->tokens[i] = ft_strdup(tmp[i]);
    cmds->tokens[i] = ft_strdup(cmds->prompt);
    cmds->tokens[i + 1] = 0;
    ft_doublefree(tmp);
}
