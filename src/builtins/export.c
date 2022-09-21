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

/**
 * @param var is the name of export variable
 * @param env struct with environment
 * @param cpy_env is a copy of the environment
 */
static void	ft_replace_env(char *var, t_env *env, char **cpy_env)
{
	int		c;
	char	*target;

	c = 0;
	while (var[c] != '=')
			c++;
	target = ft_substr(var, 0, (c + 1));
	env->env = (char **)malloc(sizeof(char *)
			* (ft_doublestrlen(cpy_env) + 1));
	c = -1;
	while (cpy_env[++c])
	{
		if (!ft_strncmp(cpy_env[c], target, ft_strlen(target)))
			env->env[c] = ft_strdup(var);
		else
			env->env[c] = ft_strdup(cpy_env[c]);
	}
	free(target);
	env->env[c] = 0;
}

/**
 * @param var is the name of exported variable
 * @param env struct with environment
 */
static void	ft_create_env_var(char *var, t_env *env)
{
	char	**cpy_env;
	int		i;

	ft_create_exp_var(var, env);
	i = -1;
	cpy_env = ft_doublestrdup(env->env);
	ft_doublefree(env->env);
	if (ft_already_in(var, cpy_env))
		ft_replace_env(var, env, cpy_env);
	else
	{
		env->env = (char **)malloc(sizeof(char *)
				* (ft_doublestrlen(cpy_env) + 2));
		while (cpy_env[++i])
			env->env[i] = ft_strdup(cpy_env[i]);
		env->env[i] = ft_strdup(var);
		env->env[i + 1] = 0;
	}
	ft_doublefree(cpy_env);
}

bool	ft_check_variable(const char *var)
{
	int	c;

	c = -1;
	while (var[++c])
	{
		if (var[c] == '=')
			return (0);
	}
	return (1);
}

/**
  * @brief check if var has = to add in export_env or in enviroment
  * @param var is the name of exported variable
  * @param env struct with environment
  */
static void	ft_export(char *var, t_env *env)
{
	char	**tmp;
	int		i;

	if (ft_check_variable(var))
	{
		tmp = ft_doublestrdup(env->exp);
		if (!ft_already_in(var, tmp))
		{
			ft_doublefree(env->exp);
			i = -1;
			env->exp = (char **)malloc(sizeof(char *)
					* (ft_doublestrlen(tmp) + 2));
			while (tmp[++i])
				env->exp[i] = ft_strdup(tmp[i]);
			env->exp[i] = ft_strdup(var);
			env->exp[i + 1] = 0;
			ft_doublefree(tmp);
			return ;
		}
		ft_doublefree(tmp);
		return ;
	}
	ft_create_env_var(var, env);
}

/**
 * -Checks if export has arguments
 * @param cmd struct with command
 * @param env struct with environment
 * @param pos_cmd number of commands
 * @param n_cmds actual command
 * @return
 */
int	ft_export_check(t_cmd *cmd, t_env *env, int pos_cmd, int n_cmds)
{
	int	pos;

	if (pos_cmd != n_cmds - 1)
		return (1);
	if (cmd->cmd[1])
	{
		pos = 1;
		while (cmd->cmd[pos])
		{
			if (ft_isalpha(cmd->cmd[pos][0]))
				ft_export(cmd->cmd[pos++], env);
			else
			{
				printf("Invalid identifier\n");
				break ;
			}
		}
	}
	else
	{
		pos = -1;
		while (env->exp[++pos])
			printf("declare -x %s\n", env->exp[pos]);
	}
	return (g_exit = 0, 0);
}
