#include "../../include/minishell.h"

/**
 * @param env struct with environment
 */
void	ft_rewrite_pwd(t_env *env)
{
	int	var;

    var = -1;
    env->pwd = getcwd(NULL, 0);
	while (env->env[++var])
	{
		if (!ft_strncmp(env->env[var], "PWD=", 4))
		{
			free(env->env[var]);
            env->env[var] = ft_strjoin("PWD=", env->pwd);
		}
	}
}


/**
 * @brief rewrite $pwd and $oldpwd in environment
 * @param env struct with environment
 */
void	ft_previous_dir(t_env *env)
{
	int		var;

    var = -1;
	while (env->env[++var])
	{
		if (!ft_strncmp(env->env[var], "OLDPWD=", 7))
		{
            env->oldpwd = ft_substr(env->env[var + 1], 4,
                                    (ft_strlen(env->env[var + 1]) - 4));
			free(env->env[var + 1]);
            env->pwd = ft_substr(env->env[var], 7,
                                 (ft_strlen(env->env[var]) - 7));
			chdir(env->pwd);
            env->env[var + 1] = ft_strjoin("PWD=", env->pwd);
			free(env->env[var]);
            env->env[var] = ft_strjoin("OLDPWD=", env->oldpwd);
			return ;
		}
	}
	printf("Minishell: cd: OLDPWD not set\n");
    env->oldpwd = NULL;
    env->pwd = NULL;
}
