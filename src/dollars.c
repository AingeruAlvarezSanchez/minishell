/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 05:09:56 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/04 16:48:39 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

static char	*ft_tofind(t_cmds *cmds, int iref, int jref)
{
	char	*to_find;
	char	*tmp;
	char	*tmp2;
	int		reference;

	reference = jref + 1;
	while (cmds->tokens[iref][jref] && cmds->tokens[iref][jref] != ' ')
		jref++;
	tmp = ft_substr(cmds->tokens[iref], reference, (jref - reference));
	tmp2 = ft_strtrim(tmp, "\"");
	free(tmp);
	to_find = ft_strjoin(tmp2, "=");
	free(tmp2);
	return (to_find);
}

static void	ft_dollar_value(t_cmds *cmds, char *to_find, int iref, int jref)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(cmds->tokens[iref], 0, jref);
	while (cmds->tokens[iref][jref] && cmds->tokens[iref][jref] != ' ')
		jref++;
	tmp2 = ft_substr(cmds->tokens[iref], jref, (ft_strlen(cmds->tokens[iref]) - jref));
	tmp3 = ft_strjoin(tmp, to_find);
	free(tmp);
	free(cmds->tokens[iref]);
	cmds->tokens[iref] = ft_strjoin(tmp3, tmp2);
	free(tmp2);
	free(tmp3);
}

static void	ft_dollar_no_value(t_cmds *cmds, int iref, int jref)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(cmds->tokens[iref], 0, jref);
	while (cmds->tokens[iref][jref] && cmds->tokens[iref][jref] != ' ')
		jref++;
	tmp2 = ft_substr(cmds->tokens[iref], (jref + 1), (ft_strlen(cmds->tokens[iref]) - (jref - 1)));
	free(cmds->tokens[iref]);
	cmds->tokens[iref] = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
}

void ft_check_dollar(t_cmds *cmds, t_data *data, int iref, int jref)
{
	char	*tmp;
	char	*to_find;
	int		i;

	if (!cmds->tokens[iref][jref + 1])
		return ;
	//if (cmds->tokens[iref][jref + 1] == '?')
		//ft_last_status();
	tmp = ft_tofind(cmds, iref, jref);
	i = -1;
	while (data->env[++i])
	{
		if (!ft_strncmp(data->env[i], tmp, ft_strlen(tmp)))
		{
			to_find = ft_substr(data->env[i], ft_strlen(tmp),
					(ft_strlen(data->env[i]) - ft_strlen(tmp)));
			free(tmp);
			ft_dollar_value(cmds, to_find, iref, jref);
			free(to_find);
			return ;
		}
	}
	free(tmp);
	ft_dollar_no_value(cmds, iref, jref);
}
