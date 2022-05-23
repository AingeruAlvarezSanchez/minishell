/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:54:34 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/20 12:25:48 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int ft_checkprevious(char *tmp)
{
    if (tmp[0])
        return (1);
    else
        return (0);
}

static void ft_multicommand(t_cmds *cmds, int iref, int xref, int cut)
{
    char    **tmp;
    char    **tmp2;
    int     i;
    int     x;

    tmp = ft_split(cmds->tokens[iref], ' ');
    if (ft_doublestrlen(tmp) == 1)
    {
        ft_doublefree(tmp);
        return ;
    }
    else
    {
        tmp2 = ft_doublestrdup(cmds->tokens);
        cmds->tokens = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) + (iref + 2)));
        i = -1;
        while (++i < iref)
            cmds->tokens[i] = ft_strdup(tmp2[i]);
        x = 0;
        while (tmp[x])
            cmds->tokens[i++] = tmp[x++];
        cmds->tokens[i] = ft_substr(cmds->prompt, xref, ((cut + 1) - xref));
        cmds->tokens[i + 1] = 0;
    }
}

static void ft_isnotfirst(t_cmds *cmds, char **tmp, int xref, int x)
{
    char    *tmp2;
    int     i;

    tmp2 = ft_substr(cmds->prompt, 0, xref);
    if (ft_checkprevious(tmp2))
    {
        cmds->tokens = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) + 3));
        i = -1;
        while (tmp[++i])
            cmds->tokens[i] = ft_strdup(tmp[i]);
        cmds->tokens[i] = ft_strtrim(tmp2, " ");
        cmds->tokens[i + 2] = 0;
        cmds->tokens[i + 1] = ft_substr(cmds->prompt, xref, ((x + 1) - xref));
        ft_multicommand(cmds, i, xref, x);
    }
    else
    {
        i = -1;
        cmds->tokens = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) + 2));
        while (tmp[++i])
            cmds->tokens[i] = ft_strdup(tmp[i]);
        cmds->tokens[i] = ft_substr(cmds->prompt, xref, ((x + 1) - xref));
        cmds->tokens[i + 1] = 0;
    }
    free(tmp2);
}

int  ft_quotes(t_cmds *cmds, int xref, char c)
{
    char    **tmp;
    int     x;

    x = xref + 1;
    tmp = ft_doublestrdup(cmds->tokens);
    if (xref != 0 && cmds->prompt[xref - 1] != ' ')
        xref = ft_composed_quotes_ref(cmds, xref);
    while (cmds->prompt[x] != c)
        x++;
    if (cmds->prompt[x + 1] && cmds->prompt[x + 1] != ' ')
        x = ft_composed_quotes_len(cmds, x);
    if (tmp[0])
        ft_isnotfirst(cmds, tmp, xref, x);
    else
    {
        cmds->tokens = (char **)malloc(sizeof(char *) * 2);
        if (cmds->prompt[x + 1] && cmds->prompt[x + 1] != '"')
            cmds->tokens[0] = ft_substr(cmds->prompt, xref, ((x + 2) - xref));
        else
            cmds->tokens[0] = ft_substr(cmds->prompt, xref, ((x + 1) - xref));
        cmds->tokens[1] = 0;
    }
    ft_doublefree(tmp);
    return (x + 1);
}