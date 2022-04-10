/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:28:58 by aalvarez          #+#    #+#             */
/*   Updated: 2022/03/31 21:28:58 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

/* This function checks wheter after the found quote if any other quotes,
if there aren't any other closing quotes, returns to prompt state*/
int	ft_quote_error(t_cmds *cmds, int iref, int jref, char quote)
{
	while (cmds->tokens[iref][jref] && cmds->tokens[iref][jref] != quote)
		jref++;
	if (cmds->tokens[iref][jref] != quote)
	{
		printf("Syntax error, unclosed quotes\n");
		return (-1);
	}
	return (jref);
}

/* This function is only called if after the last quote there are 
other characters, this exist for memory assign efficiency */
static char	**ft_full_final( t_cmds *cmds, char **tmp, int iref, int i, char quote)
{
	int	j;
	int	jref;

	while (cmds->tokens[++i])
		tmp[i] = ft_strdup(cmds->tokens[i]);
	j = 0;
	while (tmp[iref][j] != quote)
		j++;
	jref = j + 1;
	while (tmp[iref][jref] != quote)
		jref++;
	free(tmp[iref]);
	tmp[iref] = ft_substr(cmds->tokens[iref], 0, j);
	tmp[iref + 1] = ft_substr(cmds->tokens[iref], j, (jref - (j - 1)));
	tmp[iref + 2] = ft_substr(cmds->tokens[iref], (jref + 1), (ft_strlen(cmds->tokens[iref]) - (jref + 1)));
	tmp[iref + 3] = 0;
	ft_doublefree(cmds->tokens);
	return (tmp);
}

/* This function is only called if after the last quote there are no other characters,
this exist for memory assign efficiency */
static char	**ft_empty_final(t_cmds *cmds, char **tmp, int iref, int i, char quote)
{
	int	j;

	while (cmds->tokens[++i])
		tmp[i] = ft_strdup(cmds->tokens[i]);
	j = 0;
	while (tmp[iref][j] != quote)
		j++;
	tmp[iref] = ft_substr(cmds->tokens[iref], 0, j);
	tmp[iref + 1] = ft_substr(cmds->tokens[iref], j, (ft_strlen(cmds->tokens[iref]) - j));
	tmp[iref + 2] = 0;
	j = -1;
	ft_doublefree(cmds->tokens);
	return (tmp);
}

/* This function recreates the result of tmp on the 
cmds->tokens structure component */
static void	ft_newcmds(t_cmds *cmds, char **tmp)
{
	int	i;

	cmds->tokens = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) + 1));
	i = -1;
	while (tmp[++i])
		cmds->tokens[i] = ft_strdup(tmp[i]);
	cmds->tokens[i] = 0;
}

/* This function manages both simple and multiple quotes */
void	ft_quotes(t_cmds *cmds, int iref, int jref, char quote)
{
	char	**tmp;
	int		i;

	i = -1;
	if (cmds->tokens[iref][jref + 1])
	{
		tmp = (char **)malloc(sizeof(char *) * (ft_doublestrlen(cmds->tokens) + 3));
		tmp = ft_full_final(cmds, tmp, iref, i, quote);
	}
	else
	{
		tmp = (char **)malloc(sizeof(char *) * (ft_doublestrlen(cmds->tokens) + 2));
		tmp = ft_empty_final(cmds, tmp, iref, i, quote);
	}
	ft_newcmds(cmds, tmp);
	ft_doublefree(tmp);
}
