/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:46:28 by aalvarez          #+#    #+#             */
/*   Updated: 2022/09/21 19:46:28 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param env struct with environment
 * @param pwd route of pwd
 */
static void	ft_save_oldpwd(t_env *env, char *pwd)
{
	char	*var;
	int		i;

	i = -1;
	env->oldpwd = getcwd(NULL, 0);
	while (env->env[++i])
	{
		if (!ft_strncmp(env->env[i], "OLDPWD=", 7))
		{
			var = ft_strjoin("PWD=", pwd);
			if (ft_strncmp(env->env[i + 1], var, ft_strlen(var)))
			{
				free(env->env[i]);
				env->env[i] = ft_strjoin("OLDPWD=", env->oldpwd);
			}
			free(var);
			return ;
		}
	}
	ft_oldpwd(env);
}

/**
 * @brief gets $HOME for first time
 * @param env struct with the environment
 * @return $HOME variable in environment
 */
static char	*ft_init_home(t_env *env)
{
	int	i;

	i = -1;
	while (env->env[++i])
	{
		if (!ft_strncmp(env->env[i], "HOME=", 5))
			return (ft_substr(env->env[i], 5,
					ft_strlen(env->env[i]) - 5));
	}
	printf("HOME not set\n");
	return (NULL);
}

/**
 * @brief saves $OLDPWD for first time in environment
 * @param env struct with the environment
 */
void	ft_oldpwd(t_env *env)
{
	char	**nw_env;
	int		u;
	int		i;

	u = 0;
	i = -1;
	nw_env = ft_doublestrdup(env->env);
	ft_doublefree(env->env);
	env->env = (char **)malloc(sizeof(char *)
			* (ft_doublestrlen(nw_env) + 2));
	while (nw_env[++i])
	{
		if (!ft_strncmp(nw_env[i], "PWD=", 4))
			env->env[u++] = ft_strjoin("OLDPWD=", env->oldpwd);
		env->env[u++] = ft_strdup(nw_env[i]);
	}
	env->env[u] = 0;
	ft_doublefree(nw_env);
}

/**
 * @brief check if 1rst parameter is accessible by cd
 * @param cmd struct with commands
 * @param env struct with environment
 * @return true if accesible
 */
bool	ft_cd(t_cmd *cmd, t_env *env)
{
	ft_save_oldpwd(env, cmd->cmd[1]);
	if (chdir(cmd->cmd[1]) == -1)
	{
		printf("cd: %s: No such file or directory\n", cmd->cmd[1]);
		g_exit = 1;
		free(env->oldpwd);
		return (1);
	}
	ft_rewrite_pwd(env);
	return (0);
}

/**
 * @param cmd struct with commands
 * @param env struct with environment
 * @param pos_cmd command position
 * @return 1 if first command
 */
bool	ft_home_cd(t_cmd *cmd, t_env *env, int pos_cmd)
{
	char	*route;

	if (pos_cmd != 1)
		return (1);
	if (!cmd->cmd[1] || cmd->cmd[1][0] == '~')
	{
		route = ft_init_home(env);
		ft_save_oldpwd(env, route);
		chdir(route);
		ft_rewrite_pwd(env);
		free(route);
	}
	else if (cmd->cmd[1][0] == '-')
		ft_last_dir(env);
	else
		if (ft_cd(cmd, env))
			return (false);
	free(env->oldpwd);
	free(env->pwd);
	g_exit = 0;
	return (false);
}
