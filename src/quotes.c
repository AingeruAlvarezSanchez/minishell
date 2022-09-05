/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:00:45 by aalvarez          #+#    #+#             */
/*   Updated: 2022/09/05 00:53:39 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

static void	ft_isnotfirst(t_cmds *cmds, char **tmp, int xref, int x)
{
	char	*tmp2;
	int		i;

	tmp2 = ft_substr(cmds->prompt, 0, xref);
	cmds->tokens = (char **)malloc(sizeof(char *)
			* (ft_doublestrlen(tmp) + 3));
	i = -1;
	if (!ft_isempty(tmp2))
	{
		while (tmp[++i])
			cmds->tokens[i] = ft_strdup(tmp[i]);
		cmds->tokens[i] = ft_strdup(" ");
		cmds->tokens[i + 1] = ft_substr(cmds->prompt, xref, ((x + 1) - xref));
		cmds->tokens[i + 2] = 0;
	}
	else
	{
		while (tmp[++i])
			cmds->tokens[i] = ft_strdup(tmp[i]);
		cmds->tokens[i] = ft_strdup(tmp2);
		cmds->tokens[i + 1] = ft_substr(cmds->prompt, xref, ((x + 1) - xref));
		cmds->tokens[i + 2] = 0;
	}
	free(tmp2);
}

static void	ft_checkprevious(t_cmds *cmds, int xref, int x)
{
	if (xref != 0)
	{
		cmds->tokens = (char **)malloc(sizeof(char *) * 3);
		cmds->tokens[0] = ft_substr(cmds->prompt, 0, xref);
		cmds->tokens[1] = ft_substr(cmds->prompt, xref, ((x + 2) - (xref + 1)));
		cmds->tokens[2] = 0;
	}
	else
	{
		cmds->tokens = (char **)malloc(sizeof(char *) * 2);
		cmds->tokens[0] = ft_substr(cmds->prompt, xref, ((x + 2) - (xref + 1)));
		cmds->tokens[1] = 0;
	}
}

int	ft_quotes(t_cmds *cmds, int xref, char c)
{
	char	**tmp;
	int		x;

	x = xref + 1;
	while (cmds->prompt[x] != c)
		x++;
	tmp = ft_doublestrdup(cmds->tokens);
	ft_doublefree(cmds->tokens);
	if (!tmp)
	{
		if (x == (xref + 1))
		{
			cmds->tokens = (char **)malloc(sizeof(char *) * 2);
			cmds->tokens[0] = ft_strdup("");
			cmds->tokens[1] = 0;
			return (x + 1);
		}
		ft_checkprevious(cmds, xref, x);
	}
	else
		ft_isnotfirst(cmds, tmp, xref, x);
	ft_doublefree(tmp);
	return (x + 1);
}
