/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firstcase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:07:31 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/20 12:25:04 by ecorreia         ###   ########.fr       */
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

static void ft_isjoin_multicommand(t_cmds *cmds)
{
    char    **split;
    int     i; 

    split = ft_split(cmds->tokens[0], ' ');
    if (ft_doublestrlen(split) == 1)
    {
        ft_doublefree(split);
        return ;
    }
    ft_doublefree(cmds->tokens);
    i = -1;
    cmds->tokens = (char **)malloc(sizeof(char *) * (ft_doublestrlen(split) + 1));
    while (split[++i])
        cmds->tokens[i] = ft_strdup(split[i]);
    cmds->tokens[i] = 0;
}

static int ft_firstcut_quotejoin(t_cmds *cmds, int xref)
{
    int x;

    x = xref;
    while (x != 0)
    {
            if (cmds->prompt[x] == ' ')
            {
                ft_doublefree(cmds->tokens);
                cmds->tokens = (char **)malloc(sizeof(char *) * 2);
                cmds->tokens[0] = ft_substr(cmds->prompt, 0, x);
                cmds->tokens[1] = 0;
                ft_isjoin_multicommand(cmds);
                return (x);
            }
            x--;
    }
    return (x);
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
            if (cmds->prompt[x - 1] == ' ' || (cmds->prompt[x] != '"' && cmds->prompt[x] != '\''))
            {
                ft_first_cut(cmds, x);
                tmp = ft_substr(cmds->prompt, x, (ft_strlen(cmds->prompt) - x));
            }
            else
            {
                x = ft_firstcut_quotejoin(cmds, x);
                tmp = ft_substr(cmds->prompt, x, (ft_strlen(cmds->prompt) - x));
            }
            free(cmds->prompt);
            cmds->prompt = ft_strtrim(tmp, " ");
            free(tmp);
            return ;
        }
    }
}