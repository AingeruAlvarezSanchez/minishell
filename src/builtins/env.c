/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:56:12 by aalvarez          #+#    #+#             */
/*   Updated: 2022/09/21 19:56:12 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param old_pwd flag to check if OLDPWD
 * @param env environment taken from arguments
 * @return
 */
static char	**ft_init_env(bool old_pwd, char **env)
{
	char	**aux;

	if (old_pwd == 1)
		aux = (char **)malloc(sizeof(char *) * (ft_doublestrlen(env)));
	else
		aux = (char **)malloc(sizeof(char *) * (ft_doublestrlen(env) + 1));
	return (aux);
}

/**
 * @param env environment taken from arguments
 * @return
 */
char	**ft_dup_env(char **env)
{
	char	**nw_env;
	int		i;
	bool	old_pwd;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
			old_pwd = 1;
	}
	nw_env = ft_init_env(old_pwd, env);
	if (!nw_env)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
			env++;
		if (env[i])
			nw_env[i] = ft_strdup(env[i]);
	}
	nw_env[i] = 0;
	return (nw_env);
}

/**
 * @brief prints the environment
 * @param env struct with environment
 * @param cmd struct with command
 */
void	ft_env(t_env *env, t_cmd *cmd)
{
	int	var;

	if (!cmd->cmd[1])
	{
		var = -1;
		while (env->env[++var])
			printf("%s\n", env->env[var]);
		g_exit = 0;
	}
	else
	{
		printf("env: %s: No such file or directory\n", cmd->cmd[1]);
		g_exit = 1;
	}
}
