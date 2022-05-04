/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 23:41:57 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/04 01:35:33by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

static int	ft_is_special_char(char c)
{
	if (c == '\'' || c == '"' || c == '<' || c == '>'
		|| (c == '|' && (c != '\'' && c != '"')))
		return (1);
	return (0);
}

void	ft_newcmds(t_cmds *cmds, char **tmp)
{
	int	i;

	cmds->tokens = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) + 1));
	i = -1;
	while (tmp[++i])
		cmds->tokens[i] = ft_strtrim(tmp[i], " ");
	cmds->tokens[i] = 0;
}

void    ft_check_metacharacter(t_cmds *cmds, t_data *data)
{
    int	i;
	int	j;

	i = 0;
	while (cmds->tokens[i])
	{
		j = -1;
		while (cmds->tokens[i][++j])
		{
			if (cmds->tokens[i][j] == '$' && (cmds->tokens[i][0] != '\'' || cmds->tokens[i][ft_strlen(cmds->tokens[i]) - 1] != '\''))
			{
				ft_check_dollar(cmds, data, i, j);
				i = 0;
				break ;
			}
		}
		i++;
	}
}

static int  ft_manage_special_char(t_cmds *cmds, int iref, int jref, int c)
{
    int x;

    x = -1;
    if (c == '\'' || c == '"')
    {
        x = ft_has_final(cmds, iref, jref, c);
        if (x == -1)
            return (1);
        ft_quotes(cmds, iref, jref, x);
    }
    else if (c == '|' && (cmds->tokens[iref][0] != '\''
		&& cmds->tokens[iref][0] != '"'))
    {
        if (ft_check_pipes(cmds, iref, jref))
            return (1);
        cmds->n_cmds++;
    }
    else if (cmds->tokens[iref][x] == '>')
	{
		printf("redirections");
		return (1);
	} //in case of redirections we have to change the way the command struct is filled
    return (0);
}

int	ft_has_special_char(t_cmds *cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds->tokens[i])
	{
		j = 0;
		while (cmds->tokens[i][j])
		{
			if (ft_is_special_char(cmds->tokens[i][j]))
			{
				if (ft_manage_special_char(cmds, i, j, cmds->tokens[i][j]))
					return (1);
				if (i != 0)
					i++;
				break ;
			}
			j++;
		}
		i++;
	}
    ft_nonulls(cmds);
	return (0);
}