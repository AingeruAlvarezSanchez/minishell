/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:48:52 by aalvarez          #+#    #+#             */
/*   Updated: 2022/04/27 14:50:29 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_special_char(char c)
{
	if (c == '\'' || c == '"' || c == '<' || c == '>'
		|| (c == '|' && (c != '\'' && c != '"')))
		return (1);
	return (0);
}

int	ft_manage_special_char(int y, int x, t_cmds *cmds)
{
	if (cmds->tokens[y][x] == '\'' || cmds->tokens[y][x] == '"')
	{
		x = ft_quote_error(cmds, y, (x + 1), cmds->tokens[y][x]);
		if (x == -1)
			return (1);
		ft_quotes(cmds, y, x, cmds->tokens[y][x]);
	}
	else if (cmds->tokens[y][x] == '|' && (cmds->tokens[y][0] != '\''
		&& cmds->tokens[y][0] != '"'))
	{
		if (ft_check_pipes(cmds, y, x))
			return (1);
		cmds->n_cmds++;
	}
	else if (cmds->tokens[y][x] == '>')
	{
		printf("redirections");
		return (1);
	}
	return (0);
}

int	ft_has_special_char(t_cmds *cmds)
{
	int	y;
	int	x;

	y = -1;
	while (cmds->tokens[++y])
	{
		x = -1;
		while (cmds->tokens[y][++x])
		{
			if (ft_is_special_char(cmds->tokens[y][x]))
			{
				if (ft_manage_special_char(y, x, cmds))
					return (1);
				y++;
				break ;
			}
		}
	}
	return (0);
}

/**
 * @brief This function detects if there is a dollar in any
 * expandible part of the cmds->tokens array and adapts
 * it to the dollar necessities
 */
void	ft_check_metacharacter(t_cmds *cmds, t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (cmds->tokens[y])
	{
		x = -1;
		while (cmds->tokens[y][++x])
		{
			if (cmds->tokens[y][x] == '$' && cmds->tokens[y][0] != '\'')
			{
				ft_check_dollar(cmds, data, y, x);
				y = 0;
				break ;
			}
		}
		y++;
	}
}
