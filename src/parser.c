/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 21:12:02 by aalvarez          #+#    #+#             */
/*   Updated: 2022/03/28 21:15:26 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_check_env(t_data *Data, char *to_find)
{
	char	*full_value;
	int		i;
	int		j;

	i = -1;
	while (Data->env[++i])
	{
		if (!ft_strncmp(Data->env[i], to_find, ft_strlen(to_find)))
		{
			j = 0;
			while (Data->env[i][j] != '=')
				j++;
			full_value = ft_substr(Data->env[i], (j + 1), ft_strlen(Data->env[i]));
			return (full_value);
		}
	}
	return (NULL);
}

void	ft_reshape_cmds( t_cmds *Cmds, char *value, int iref)
{
	int		j;
	int		jref;
	char	*tmp;

	j = -1;
	tmp = ft_strdup(Cmds->commands[iref]);
	while (Cmds->commands[iref][++j])
	{
		if (Cmds->commands[iref][j] == '$')
		{
			jref = j;
			while (Cmds->commands[iref][j] && Cmds->commands[iref][j] != ' ')
				j++;
			Cmds->commands[iref] = ft_substr(Cmds->commands[iref], 0, jref);
			tmp = ft_substr(tmp, j, ft_strlen(tmp));
			Cmds->commands[iref] = ft_strjoin(Cmds->commands[iref], value);
			Cmds->commands[iref] = ft_strjoin(Cmds->commands[iref], tmp);
		}
	}
}

void	ft_getvalue(t_cmds *Cmds, t_data *Data, int iref, int jref)
{
	char	*to_find;
	char	*value;
	int		j;
	int		i;

	j = jref + 1;
	while (Cmds->commands[iref][jref] && Cmds->commands[iref][jref] != ' ')
			jref++;
	to_find = (char *)malloc(sizeof(char) * (jref + 1));
	i = 0;
	while (Cmds->commands[iref][j] && Cmds->commands[iref][j] != ' ')
		to_find[i++] = Cmds->commands[iref][j++];
	to_find[i] = 0;
	value = ft_check_env(Data, to_find);
	if (value)
		ft_reshape_cmds(Cmds, value, iref);
}

void	ft_split_dollar(t_cmds *Cmds, t_data *Data)
{
	int	i;
	int	j;

	i = -1;
	while (Cmds->commands[++i])
	{
		j = -1;
		while (Cmds->commands[i][++j])
		{
			if (Cmds->commands[i][j] == '$')
			{
				if (Cmds->commands[i][j + 1] != ' ' && Cmds->commands[i][j + 1] != '?')
					ft_getvalue(Cmds, Data, i, j);
				/*else if (Cmds->commands[i][j + 1] == '?')
					ft_last_output(Cmds);*/
			}
		}
	}
}

void	ft_check_separators(t_cmds *Cmds, t_data *Data)
{
	int	j;

	j = -1;
	while (Cmds->commands[0][++j])
	{
		if (Cmds->commands[0][j] == '|')
			Cmds->pipes = 1;
		else if (Cmds->commands[0][j] == '$')
			Cmds->dollar = 1;
		/*else if (Cmds->commands[i][j] == '"' || str[i] == '\'')
			Cmds->quotes = 1;*/
	}
	if (Cmds->pipes == 1)
		Cmds->commands = ft_split(Cmds->commands[0], '|');
	if (Cmds->dollar == 1)
		ft_split_dollar(Cmds, Data);
	/*else if (Cmds->quotes == 1)
		ft_split_quotes();*/
}