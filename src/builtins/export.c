/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:17:10 by ecorreia          #+#    #+#             */
/*   Updated: 2022/09/16 21:21:19 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_replace_env(char *variable, t_env *msh, char **tmp)
{
	int		x;
	char	*to_search;

	x = 0;
	while (variable[x] != '=')
			x++;
	to_search = ft_substr(variable, 0, (x + 1));
	msh->env = (char **)malloc(sizeof(char *)
                               * (ft_doublestrlen(tmp) + 1));
	x = -1;
	while (tmp[++x])
	{
		if (!ft_strncmp(tmp[x], to_search, ft_strlen(to_search)))
			msh->env[x] = ft_strdup(variable);
		else
			msh->env[x] = ft_strdup(tmp[x]);
	}
	free(to_search);
	msh->env[x] = 0;
}

static void	ft_create_env_var(char *variable, t_env *msh)
{
	char	**tmp;
	int		i;

	ft_create_exp_var(variable, msh);
	i = -1;
	tmp = ft_doublestrdup(msh->env);
	ft_doublefree(msh->env);
	if (ft_already_in(variable, tmp))
		ft_replace_env(variable, msh, tmp);
	else
	{
		msh->env = (char **)malloc(sizeof(char *)
                                   * (ft_doublestrlen(tmp) + 2));
		while (tmp[++i])
			msh->env[i] = ft_strdup(tmp[i]);
		msh->env[i] = ft_strdup(variable);
		msh->env[i + 1] = 0;
	}
	ft_doublefree(tmp);
}

/**
 * @brief check if variable has = to add in export_env or in enviroment
 */
static void	ft_export(char *variable, t_env *msh)
{
	char	**tmp;
	int		i;

	if (ft_check_variable(variable))
	{
		tmp = ft_doublestrdup(msh->exp);
		ft_doublefree(msh->exp);
		i = -1;
		msh->exp = (char **)malloc(sizeof(char *)
                                   * (ft_doublestrlen(tmp) + 2));
		while (tmp[++i])
			msh->exp[i] = ft_strdup(tmp[i]);
		msh->exp[i] = ft_strdup(variable);
		msh->exp[i + 1] = 0;
		ft_doublefree(tmp);
		return ;
	}
	ft_create_env_var(variable, msh);
}

/**
 * @brief   -Checks if export has arguments
 *          -Check if variables are alphabetic
 */
int	ft_export_check(t_cmd *command, t_env *msh, int c_num, int count)
{
	int	i;

	if (c_num != count - 1)
		return (1);
	if (command->cmd[1])
	{
		i = 1;
		while (command->cmd[i])
		{
			if (ft_isalpha(command->cmd[i][0]))
				ft_export(command->cmd[i++], msh);
			else
			{
				printf("Invalid identifier\n");
				break ;
			}
		}
	}
	else
	{
		i = -1;
		while (msh->exp[++i])
			printf("declare -x %s\n", msh->exp[i]);
	}
	return (g_exit_status = 0, 0);
}

bool	ft_check_variable(char *variable)
{
	int	i;

	i = -1;
	while (variable[++i])
	{
		if (variable[i] == '=')
			return (false);
	}
	return (true);
}
