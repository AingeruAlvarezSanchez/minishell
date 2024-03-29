/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:06:06 by aalvarez          #+#    #+#             */
/*   Updated: 2022/09/21 20:06:06 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_last_nopipe(const char *prompt)
{
	int		i;
	char	last;

	i = 0;
	last = ' ';
	if (prompt != NULL)
	{
		while (prompt[i])
		{
			if (prompt[i] != 32)
				last = prompt[i];
			i++;
		}
	}
	if (last == '|')
		return (true);
	return (false);
}

static int	ft_n_pipes(char *prompt)
{
	int	quote;
	int	c;
	int	n_pipes;

	c = 0;
	n_pipes = 0;
	while (c < ft_strlen(prompt) && prompt[c])
	{
		if (prompt[c] == '\"' || prompt[c] == '\'')
		{
			quote = prompt[c];
			c++;
			while (prompt[c] && prompt[c] != quote)
				c++;
		}	
		if (prompt[c] == '|')
			n_pipes++;
		c++;
	}
	return (n_pipes);
}

bool	ft_create_cmds(char *prompt, int n_cmds, t_cmds_all *cmds)
{
	int			i;
	char		**chopped;

	i = 0;
	cmds->cmds = (t_cmd *)malloc(sizeof(t_cmd) * n_cmds);
	chopped = mini_split(prompt, '|');
	while (chopped[i])
	{	
		if (ft_check_null_cmd(chopped[i]))
			return (true);
		if (ft_has_redir(chopped[i]))
			return (true);
		cmds->cmds[i].cmd = mini_split(chopped[i], ' ');
		i++;
	}
	ft_doublefree(chopped);
	return (false);
}

/* Cleans de prompt and puts in to cmd cmds */
int	ft_parser(char *prompt, t_cmds_all *cmds)
{
	int		n_cmds;

	if (ft_last_nopipe(prompt))
		return (8);
	if (ft_process_quotes(prompt))
		return (5);
	if (ft_clean_pipes(prompt))
		return (5);
	n_cmds = ft_n_pipes(prompt) + 1;
	if (ft_create_cmds(prompt, n_cmds, cmds))
		return (12);
	cmds->n_cmds = n_cmds;
	return (1);
}

bool	ft_clean_pipes(char *str)
{
	int	i;
	int	bef_char;

	i = 1;
	bef_char = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[bef_char] == '|')
			return (true);
		i++;
		bef_char++;
	}
	return (false);
}
