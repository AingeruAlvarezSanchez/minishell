/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 23:22:38 by aalvarez          #+#    #+#             */
/*   Updated: 2022/09/05 01:00:02 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_trimquotes(t_cmds *cmds)
{
	int		i;
	char	*tmp;

	i = -1;
	while (cmds->tokens[++i])
	{
		if (cmds->tokens[i][0] == '"'
				&& cmds->tokens[i][ft_strlen(cmds->tokens[i]) - 1] == '"')
		{
			tmp = ft_strtrim(cmds->tokens[i], "\"");
			free(cmds->tokens[i]);
			cmds->tokens[i] = ft_strdup(tmp);
			free(tmp);
		}
		else
		{
			tmp = ft_strtrim(cmds->tokens[i], "'");
			free(cmds->tokens[i]);
			cmds->tokens[i] = ft_strdup(tmp);
			free(tmp);
		}
		printf("token: ///%s///\n", cmds->tokens[i]);
	}
}

static int	ft_find_next_pipe(t_cmds *cmds, int xref)
{
	while (cmds->tokens[xref] && cmds->tokens[xref][0] != '|')
		xref++;
	if (!ft_isempty(cmds->tokens[xref + 1]))
		xref++;
	return (xref + 1);
}

static void	ft_noquotes_binary(t_cmds *cmds, int i, int x)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = ft_strtrim(cmds->tokens[x], " ");
	while (tmp[j] && tmp[j] != ' ')
		j++;
	cmds->binary[i] = ft_substr(tmp, 0, j);
	free(tmp);
}

static void	ft_getbinary(t_cmds *cmds)
{
	int	i;
	int	x;

	i = -1;
	x = 0;
	cmds->binary = (char **)malloc(sizeof(char *) * (cmds->n_cmds + 1));
	while (++i < cmds->n_cmds)
	{
		if (cmds->tokens[x][0] == '"' || cmds->tokens[x][0] == '\'')
		{
			if (cmds->tokens[x][0] == '"')
				cmds->binary[i] = ft_strtrim(cmds->tokens[x], "\"");
			else
				cmds->binary[i] = ft_strtrim(cmds->tokens[x], "\'");
		}
		else
			ft_noquotes_binary(cmds, i, x);
		if (cmds->n_cmds > 1 && i != cmds->n_cmds - 1)
			x = ft_find_next_pipe(cmds, x);
		printf("binary: --%s--\n", cmds->binary[i]);
	}
	cmds->binary[i] = 0;
}

void	ft_parsing(t_cmds *cmds)
{
	ft_getbinary(cmds);
	ft_trimquotes(cmds);
}
