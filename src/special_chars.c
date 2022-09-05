/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:44:55 by aalvarez          #+#    #+#             */
/*   Updated: 2022/09/04 22:24:11 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_is_special_char(char c)
{
	if (c == '\'' || c == '"' || c == '|')
		return (1);
	return (0);
}

static int	ft_manage_special_character(t_cmds *cmds, int xref, char c)
{
	int			result;
	static int	check;

	result = 0;
	if (c == '\'' || c == '"')
	{
		if (!ft_has_final(cmds, xref, c))
			return (-1);
		result = ft_quotes(cmds, xref, c);
	}
	else if (c == '|')
	{
		if (ft_pipes_error(cmds, xref, check))
			return (-1);
		result = ft_pipes(cmds, xref);
		cmds->n_cmds++;
		check = 1;
	}
	return (result);
}

int	ft_has_special_char(t_cmds *cmds)
{
	char	*tmp;
	int		x;
	int		ref;

	x = -1;
	while (cmds->prompt[++x])
	{
		if (ft_is_special_char(cmds->prompt[x]))
		{
			ref = ft_manage_special_character(cmds, x, cmds->prompt[x]);
			if (ref == -1)
				return (1);
			tmp = ft_substr(cmds->prompt, ref, ft_strlen(cmds->prompt));
			free(cmds->prompt);
			if (!tmp)
			{
				free(tmp);
				break ;
			}
			cmds->prompt = ft_strdup(tmp);
			free(tmp);
			x = -1;
		}
	}
	return (0);
}
