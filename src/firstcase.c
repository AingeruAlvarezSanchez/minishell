/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firstcase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:07:31 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/16 06:06:55 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void ft_isfirst_multicommand(t_cmds *cmds)
{
    char    **tmp;

    tmp = ft_split(cmds->tokens[0], ' ');
    if (ft_doublestrlen(tmp) == 1)
    {
        ft_doublefree(tmp);
        return ;
    }
    else
    {
        ft_doublefree(cmds->tokens);
        cmds->tokens = ft_doublestrdup(tmp);
    }
}

static void  ft_first_cut(t_cmds *cmds, int xref)
{
    char    *tmp;

    ft_doublefree(cmds->tokens);
    cmds->tokens = (char **)malloc(sizeof(char *) * 2);
    tmp = ft_substr(cmds->prompt, 0, xref);
    cmds->tokens[0] = ft_strtrim(tmp, " ");
    cmds->tokens[1] = 0;
    free(tmp);
    ft_isfirst_multicommand(cmds);
}

void ft_check_first(t_cmds *cmds)
{
    char    *tmp;
    int     x;

    x = -1;
    while (cmds->prompt[++x])
    {
        if (ft_is_special_char(cmds->prompt[x]))
        {
            if (x == 0)
                return ;
            ft_first_cut(cmds, x);
            tmp = ft_substr(cmds->prompt, x, (ft_strlen(cmds->prompt) - x));
            free(cmds->prompt);
            cmds->prompt = ft_strdup(tmp);
            free(tmp);
            return ;
        }
    }
}