/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:29:07 by aalvarez          #+#    #+#             */
/*   Updated: 2022/03/31 21:29:07 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* This function creates the string to search on the environment */
static char	*ft_tofind(t_cmds *cmds, int iref, int jref)
{
	char	*to_find;
	char	*tmp;
	char	*tmp2;
	int		reference;

	reference = jref + 1;
	while (cmds->tokens[iref][jref] && cmds->tokens[iref][jref] != ' ')
		jref++;
	to_find = ft_substr(cmds->tokens[iref],reference, jref -1);
	tmp = ft_strtrim(to_find, "\"");
	free(to_find);
	tmp2 = ft_strjoin(tmp, "=");
	free(tmp);
	return (tmp2);
}

/* This function is only called if the value inside the dollar is actually in
the environment variable, it isn't used otherwise */
static void	ft_dollar_value(t_cmds *cmds, char *to_find, int iref, int jref)
{
	char	**tmp;
	char	*tmp2;
	char	*tmp3;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * (ft_doublestrlen(cmds->tokens) + 1));
	i = -1;
	while (cmds->tokens[++i])
		tmp[i] = ft_strdup(cmds->tokens[i]);
	tmp[i] = 0;
	tmp2 = ft_substr(tmp[iref], 0, jref);
	tmp3 = ft_strjoin(tmp2, to_find);
	free(tmp2);
	tmp2 = ft_strtrim(tmp3, "\"");
	free(tmp3);
	while (cmds->tokens[iref][jref] && cmds->tokens[iref][jref] != ' ')
		jref++;
	tmp3 = ft_substr(tmp[iref], jref, (ft_strlen(tmp[iref]) - jref));
	free(tmp[iref]);
	tmp[iref] = ft_strdup(tmp3);
	free(tmp3);
	tmp3 = ft_strjoin(tmp2, tmp[iref]);
	free(tmp[iref]),
	tmp[iref] = ft_strdup(tmp3);
	free(tmp3);
	ft_doublefree(cmds->tokens);
	i = -1;
	cmds->tokens = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) + 1));
	while (tmp[++i])
		cmds->tokens[i] = ft_strdup(tmp[i]);
	cmds->tokens[i] = 0;
	ft_doublefree(tmp);
	free(tmp2);
}

/* This function is only called if the value inside the dollar
is not inside the environment varible, it changes the dollar value
to null, exactly like in bash */
static void	ft_dollar_no_value(t_cmds *cmds, int iref, int jref)
{
	char	*tmp;
	tmp = ft_substr(cmds->tokens[iref], 0, jref);
	while (cmds->tokens[iref][jref] && cmds->tokens[iref][jref] != ' ')
		iref++;
	cmds->tokens[iref] = ft_substr(cmds->tokens[iref],
			jref, ft_strlen(cmds->tokens[iref]));
	tmp = ft_strjoin(tmp, cmds->tokens[iref]);
	tmp = ft_strtrim(tmp, "\"");
	free(cmds->tokens[iref]);
	cmds->tokens[iref] = ft_strdup(tmp);
	free(tmp);
}

/* This function is the entrance to checking all the possibilites for the $
caracter, that means expansion for environment variable or last status */
void	ft_check_dollar(t_cmds *cmds, t_data *data, int iref, int jref)
{
	char	*to_find;
	char	*tmp;
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
			if(to_find)
			{
				ft_dollar_value(cmds, to_find, iref, jref);
				free(tmp);
				free(to_find);
				return ;
			}
		}
	}
	free(tmp);
	ft_dollar_no_value(cmds, iref, jref);
}
