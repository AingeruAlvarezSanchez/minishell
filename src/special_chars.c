/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 09:51:44 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/21 01:51:29by aalvarez         ###   ########.fr       */
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

int	ft_is_pipe_or_redir(char c)
{
	if (c == '<' || c == '>' || (c == '|'))
		return (1);
	return (0);
}

static int  ft_manage_special_character(t_cmds *cmds, int xref, char c)
{
    int result;
    char *sp;
    char *prompt = ft_substr(cmds->prompt, xref + 1, sizeof(cmds->prompt) - xref);

	result = 0;
    if ((c == '<' || c == '>') &&  *prompt == c)//append
    {
        sp = malloc(sizeof(char) * 3);
        sp[0] = c;
        sp[1] = c;
        sp[2] = 0;

        if (ft_pipes_error(++prompt, sp))
            return (-1);

        result = ft_pipes(cmds, xref, sp);
        cmds->n_cmds++;
        return (result);
    }
    sp = malloc(sizeof(char) * 2);
    sp[0] = c;
    sp[1] = 0;
    if (c == '<' || c == '>' || c == '|')
    { 
        if (ft_pipes_error(prompt, sp))
            return (-1);
        result = ft_pipes(cmds, xref, sp);
        cmds->n_cmds++;
    }
    else if (c == '"' || c == '\'')
    {
        if (!ft_has_final(cmds, xref, c))
            return (-1);
        result = ft_quotes(cmds, xref, c);
    }
    free(sp);
    free(prompt);
    return (result);
}

int ft_has_special_char(t_cmds *cmds)
{
    char    *tmp;
    int     x;
    int     ref;
    int     check;

    x = -1;
    check = 0;
    check = ft_check_first(cmds);
    while (cmds->prompt[++x])
    {
        if (ft_is_special_char(cmds->prompt[x]))
        {
            ref = ft_manage_special_character(cmds, x, cmds->prompt[x]);
            if (ref == -1)
                return (1);
            tmp = ft_substr(cmds->prompt, ref, (ft_strlen(cmds->prompt) - ref));
            free(cmds->prompt);
            check = 1;
            if (!tmp[0])
            {
                cmds->prompt = ft_strdup("");
                free(tmp);
                break ;
            }
            cmds->prompt = ft_strtrim(tmp, " ");
            free(tmp);
            x = -1;
        }
    }
    if (cmds->prompt[0])
        ft_lastjoin(cmds, check);
    return (0);
}