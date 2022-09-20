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
	int		i;
	int		u;
	char	**nw_env;

	i = -1;
    u = 0;
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
bool	cd_extension(t_cmd *cmd, t_env *env)
{
    ft_save_oldpwd(env, cmd->cmd[1]);
	if (chdir(cmd->cmd[1]) == -1)
	{
		printf("cd: %s: No such file or directory\n", cmd->cmd[1]);
		g_exit_status = 1;
		free(env->oldpwd);
		return (true);
	}
    ft_rewrite_pwd(env);
	return (false);
}

/**
 * @param cmd struct with commands
 * @param env struct with environment
 * @param pos_cmd command position
 * @return true if first command
 */
bool	ft_home_cd(t_cmd *cmd, t_env *env, int pos_cmd)
{
	char	*route;

	if (pos_cmd != 1)
		return (true);
	if (!cmd->cmd[1] || cmd->cmd[1][0] == '~')
	{
        route = ft_init_home(env);
        ft_save_oldpwd(env, route);
		chdir(route);
        ft_rewrite_pwd(env);
		free(route);
	}
	else if (cmd->cmd[1][0] == '-')
		ft_previous_dir(env);
	else
		if (cd_extension(cmd, env))
			return (false);
	free(env->oldpwd);
	free(env->pwd);
	g_exit_status = 0;
	return (false);
}
