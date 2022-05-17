/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 09:51:44 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/16 19:42:20 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

int	ft_is_special_char(char c)
{
	if (c == '\'' || c == '"' || c == '<' || c == '>'
		|| (c == '|' && (c != '\'' && c != '"')))
		return (1);
	return (0);
}

static int  ft_manage_special_character(t_cmds *cmds, int xref, char c)
{
    int result;

    if (c == '"' || c == '\'')
    {
        if (!ft_has_final(cmds, xref, c))
            return (-1);
        result = ft_quotes(cmds, xref, c);
    }
    else if (c == '|')
    {
        if (ft_pipes_error(cmds, xref))
            return (-1);
        result = ft_pipes(cmds, xref);
    }
    else if (c == '<' || c == '>')
        printf("redirections\n");
    return (result);
}

int ft_has_special_char(t_cmds *cmds)
{
    char    *tmp;
    int     x;
    int     ref;

    x = -1;
    ft_check_first(cmds);
    while (cmds->prompt[++x])
    {
        if (ft_is_special_char(cmds->prompt[x]))
        {
            ref = ft_manage_special_character(cmds, x, cmds->prompt[x]);
            if (ref == -1)
                return (1);
            tmp = ft_substr(cmds->prompt, ref, (ft_strlen(cmds->prompt) - ref));
            free(cmds->prompt);
            cmds->prompt = ft_strtrim(tmp, " ");
            free(tmp);
            x = -1;
        }
    }
    if (cmds->prompt[0])
        ft_lastjoin(cmds);
    return (0);
}