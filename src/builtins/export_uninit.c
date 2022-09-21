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

/**
 * @param var is the name of exported variable
 * @param cpy_env copy of the environment
 * @return 1 if its inside env
 */
bool	ft_already_in(char *var, char **cpy_env)
{
	int		i;
	char	*target;

	i = 0;
	while (var[i] != '=' && var[i] != 0)
		i++;
	target = ft_substr(var, 0, (i + 1));
	while (cpy_env[++i])
	{
		if (!ft_strncmp(cpy_env[i], target, ft_strlen(target)))
		{
			free(target);
			return (1);
		}
	}
	free(target);
	return (0);
}

/**
 * @param var is the name of exported variable
 * @param cpy_env copy of the environment
 * @return 1 if its inside env
 */
bool	ft_already_exp(char *var, char **cpy_env)
{
	int		i;
	char	*target;

	i = 0;
	while (var[i] != '=')
		i++;
	target = ft_substr(var, 0, (i));
	while (cpy_env[++i])
	{
		if (!ft_strncmp(cpy_env[i], target, ft_strlen(target)))
		{
			free(target);
			return (1);
		}
	}
	free(target);
	return (0);
}

/**
 *
 * @param var is the name of exported variable
 * @param env struct with environment
 * @param cpy_env copy of the environment
 */
static void	ft_replace_exp(char *var, t_env *env, char **cpy_env)
{
	int		i;
	char	*target;

	i = 0;
	while (var[i] != '=')
		i++;
	target = ft_substr(var, 0, (i));
	env->exp = (char **)malloc(sizeof(char *)
			* (ft_doublestrlen(cpy_env) + 1));
	i = -1;
	while (cpy_env[++i])
	{
		if (!ft_strncmp(cpy_env[i], target, ft_strlen(target)))
			env->exp[i] = ft_strdup(var);
		else
			env->exp[i] = ft_strdup(cpy_env[i]);
	}
	free(target);
	env->exp[i] = 0;
}

/**
 * creates variable in export environment
 * @param var is the name of exported variable
 * @param env struct with environment
 */
void	ft_create_exp_var(char *var, t_env *env)
{
	char	**cpy_env;
	int		i;

	i = -1;
	cpy_env = ft_doublestrdup(env->exp);
	ft_doublefree(env->exp);
	if (ft_already_exp(var, cpy_env))
		ft_replace_exp(var, env, cpy_env);
	else
	{
		env->exp = (char **)malloc(sizeof(char *)
				* (ft_doublestrlen(cpy_env) + 2));
		while (cpy_env[++i])
			env->exp[i] = ft_strdup(cpy_env[i]);
		env->exp[i] = ft_strdup(var);
		env->exp[i + 1] = 0;
	}
	ft_doublefree(cpy_env);
}
