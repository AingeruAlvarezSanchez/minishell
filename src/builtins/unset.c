#include "../../include/minishell.h"

/**
 * check if inside environment
 * @param var is the name of exported variable
 * @param env struct with environment
 * @return 0 if inside env
 */
static bool	ft_not_env(char *var, t_env *env)
{
	int	i;

	i = -1;
	while (env->env[++i])
	{
		if (!ft_strncmp(env->env[i], var, (ft_strlen(var))))
			return (0);
	}
	return (1);
}

/**
 * @param var is the name of exported variable
 * @param env struct with environment
 */
static void	ft_unset(char *var, t_env *env)
{
	int		x;
	char	**tmp;
	int		i;

	if (ft_not_env(var, env))
		return ;
	else
	{
		tmp = ft_doublestrdup(env->env);
		ft_doublefree(env->env);
        env->env = (char **)malloc(sizeof(char *)
                                   * (ft_doublestrlen(tmp)));
		x = -1;
		i = -1;
		while (tmp[++i])
		{
			if (ft_strncmp(tmp[i], var, ft_strlen(var)))
                env->env[++x] = ft_strdup(tmp[i]);
		}
        env->env[x + 1] = 0;
	}
	ft_doublefree(tmp);
}

/**
 * @param var is the name of exported variable
 * @param env struct with environment
 * @return 0 if is in export environment
 */
static bool	ft_not_exp(char *var, t_env *env)
{
    int	i;

    i = -1;
    while (env->exp[++i])
    {
        if (!ft_strncmp(env->exp[i], var, (ft_strlen(var))))
            return (0);
    }
    return (1);
}

/**
 * delete var from export environment
 * @param var is the name of exported variable
 * @param env struct with environment
 */
static void	ft_unset_exp(char *var, t_env *env)
{
    int		x;
    int		i;
    char	**aux;

    if (ft_not_exp(var, env))
        return ;
    else
    {
        aux = ft_doublestrdup(env->exp);
        ft_doublefree(env->exp);
        env->exp = (char **)malloc(sizeof(char *)
                                   * (ft_doublestrlen(aux)));
        i = -1;
        x = -1;
        while (aux[++i])
        {
            if (ft_strncmp(aux[i], var, ft_strlen(var)))
                env->exp[++x] = ft_strdup(aux[i]);
        }
        env->exp[x + 1] = 0;
    }
    ft_doublefree(aux);
}

/**
 * @param cmd struct with command
 * @param env struct with environment
 * @param pos_cmd number of commands
 * @param n_cmds actual command
 * @return
 */
bool	ft_check_unset(t_cmd *cmd, t_env *env, int pos_cmd, int n_cmds)
{
	int	pos;

	if (pos_cmd != n_cmds - 1)
		return (1);
	if (cmd->cmd[1])
	{
        pos = 0;
		while (cmd->cmd[++pos])
		{
			if (ft_check_variable(cmd->cmd[pos]))
            {
				ft_unset(cmd->cmd[pos], env);
                ft_unset_exp(cmd->cmd[pos], env);
            }
		}
	}
    g_exit = 0;
	return (0);
}
