/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   composed_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:32:47 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/20 01:33:59 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int  ft_composed_quotes_ref(t_cmds *cmds, int xref)
{
    int x;

    x = xref;
    while (x != 0)
    {
        if (cmds->prompt[x] == ' ')
            return (x);
        x--;
    }
    return (x);
}

int  ft_composed_quotes_len(t_cmds *cmds, int xref)
{
    while (cmds->prompt[++xref])
    {
        if (cmds->prompt[xref] == ' ')
            return (xref - 1);
    }
    return (xref);
}
