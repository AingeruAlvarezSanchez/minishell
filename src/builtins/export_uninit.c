/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_uninit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:12:53 by ecorreia          #+#    #+#             */
/*   Updated: 2022/09/16 21:14:19 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_already_in(char *variable, char **env)
{
	int		i;
	char	*to_search;

	i = 0;
	while (variable[i] != '=')
		i++;
	to_search = ft_substr(variable, 0, (i + 1));
	while (env[++i])
	{
		if (!ft_strncmp(env[i], to_search, ft_strlen(to_search)))
		{
			free(to_search);
			return (true);
		}
	}
	free(to_search);
	return (false);
}

bool	ft_already_exp(char *variable, char **env)
{
	int		i;
	char	*to_search;

	i = 0;
	while (variable[i] != '=')
		i++;
	to_search = ft_substr(variable, 0, (i));
	while (env[++i])
	{
		if (!ft_strncmp(env[i], to_search, ft_strlen(to_search)))
		{
			free(to_search);
			return (true);
		}
	}
	free(to_search);
	return (false);
}

static void	ft_replace_exp(char *variable, t_msh_var *msh, char **tmp)
{
	int		x;
	char	*to_search;

	x = 0;
	while (variable[x] != '=')
		x++;
	to_search = ft_substr(variable, 0, (x));
	msh->exp_envp = (char **)malloc(sizeof(char *)
			* (ft_doublestrlen(tmp) + 1));
	x = -1;
	while (tmp[++x])
	{
		if (!ft_strncmp(tmp[x], to_search, ft_strlen(to_search)))
			msh->exp_envp[x] = ft_strdup(variable);
		else
			msh->exp_envp[x] = ft_strdup(tmp[x]);
	}
	free(to_search);
	msh->exp_envp[x] = 0;
}

void	ft_create_exp_var(char *variable, t_msh_var *msh)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = ft_doublestrdup(msh->exp_envp);
	ft_doublefree(msh->exp_envp);
	if (ft_already_exp(variable, tmp))
		ft_replace_exp(variable, msh, tmp);
	else
	{
		msh->exp_envp = (char **)malloc(sizeof(char *)
				* (ft_doublestrlen(tmp) + 2));
		while (tmp[++i])
			msh->exp_envp[i] = ft_strdup(tmp[i]);
		msh->exp_envp[i] = ft_strdup(variable);
		msh->exp_envp[i + 1] = 0;
	}
	ft_doublefree(tmp);
}
