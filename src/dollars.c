/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:49:43 by aalvarez          #+#    #+#             */
/*   Updated: 2022/09/04 23:59:35 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_check_dollars(t_cmds *cmds, t_data *data, int iref, int xref)
{
	char	*tmp;
	char	*tmp2;
	int		x;

	x = xref + 1;
	while (cmds->tokens[iref][x] && cmds->tokens[iref][x] != ' ')
		x++;
	if (cmds->tokens[iref][x - 1] == '"')
		tmp2 = ft_substr(cmds->tokens[iref], (xref + 1), ((x - 2) - xref));
	else
		tmp2 = ft_substr(cmds->tokens[iref], (xref + 1), (x - (xref + 1)));
	tmp = ft_strjoin(tmp2, "=");
	free(tmp2);
	x = -1;
	while (data->env[++x])
	{
		if (!ft_strncmp(data->env[x], tmp, ft_strlen(tmp)))
		{
			cmds->token_value = ft_substr(data->env[x], ft_strlen(tmp),
					(ft_strlen(data->env[x]) - ft_strlen(tmp)));
			return (free(tmp), 1);
		}
	}
	return (free(tmp), 0);
}

static void	ft_lastout_dollar(t_cmds *cmds, int iref, int xref, t_data *data)
{
	char	*status;
	char	*prev;
	char	*next;

	status = ft_itoa(data->g_last_out);
	prev = ft_substr(cmds->tokens[iref], 0, xref);
	next = ft_strjoin(prev, status);
	free(prev);
	while (cmds->tokens[iref][xref] && cmds->tokens[iref][xref] != ' ')
		xref++;
	if (cmds->tokens[iref][xref - 1] == '"')
		prev = ft_strdup("\"");
	else
		prev = ft_substr(cmds->tokens[iref], xref,
				(ft_strlen(cmds->tokens[iref]) - xref));
	free(cmds->tokens[iref]);
	cmds->tokens[iref] = ft_strjoin(next, prev);
	free(prev);
	free(status);
	free(next);
}

static void	ft_dollar_value(t_cmds *cmds, int iref, int xref)
{
	char	*prev;
	char	*next;

	prev = ft_substr(cmds->tokens[iref], 0, xref);
	next = ft_strjoin(prev, cmds->token_value);
	free(prev);
	while (cmds->tokens[iref][xref] && cmds->tokens[iref][xref] != ' ')
		xref++;
	if (cmds->tokens[iref][xref - 1] == '"')
		prev = ft_strdup("\"");
	else
		prev = ft_substr(cmds->tokens[iref], xref,
				(ft_strlen(cmds->tokens[iref]) - xref));
	free(cmds->tokens[iref]);
	cmds->tokens[iref] = ft_strjoin(next, prev);
	free(cmds->token_value);
	free(prev);
	free(next);
}

static void	ft_dollar_no_value(t_cmds *cmds, int iref, int xref)
{
	char	*prev;
	char	*next;

	prev = ft_substr(cmds->tokens[iref], 0, xref);
	xref++;
	while (cmds->tokens[iref][xref] && cmds->tokens[iref][xref] != ' ')
		xref++;
	if (cmds->tokens[iref][xref - 1] == '"')
		next = ft_strdup("\"");
	else
		next = ft_substr(cmds->tokens[iref], xref,
				(ft_strlen(cmds->tokens[iref]) + 1) - xref);
	free(cmds->tokens[iref]);
	cmds->tokens[iref] = ft_strjoin(prev, next);
	free(next);
	free(prev);
}

void	ft_dollars(t_cmds *cmds, t_data *data)
{
	int	i;
	int	x;

	i = -1;
	while (cmds->tokens[++i])
	{
		x = -1;
		while (cmds->tokens[i][++x])
		{
			if (cmds->tokens[i][x] == '$' && (cmds->tokens[i][0] != '\''
					&& cmds->tokens[i][ft_strlen(cmds->tokens[i])] != '\'')
					&& (cmds->tokens[i][x + 1]
					&& cmds->tokens[i][x + 1] != ' '))
			{
				if (cmds->tokens[i][x + 1] == '?')
				{
					ft_lastout_dollar(cmds, i, x, data);
					x = -1;
					continue ;
				}
				if (ft_check_dollars(cmds, data, i, x))
					ft_dollar_value(cmds, i, x);
				else
					ft_dollar_no_value(cmds, i, x);
				x = -1;
			}
		}
	}
}
