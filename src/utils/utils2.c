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
void	ft_last_dir(t_env *env)
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

static int	ft_get_pos(int pos, char *raw_cmd)
{
	int	i;

	while (++pos < ft_strlen(raw_cmd))
	{
		if (raw_cmd[pos] == '\'' || raw_cmd[pos] == '"')
		{
            i = pos + 1;
			while (raw_cmd[i])
			{
				if (raw_cmd[i] == raw_cmd[pos])
				{
                    pos = i;
					break ;
				}
				i++;
			}
			if (pos == i)
				continue ;
			return (1);
		}
	}
	return (0);
}

int	ft_process_quotes(char *raw_cmd)
{
	int		pos;

    pos = -1;
	if (!raw_cmd)
        raw_cmd = NULL;
	if (ft_get_pos(pos, raw_cmd))
		return (1);
	return (0);
}

bool	ft_check_null_cmd(char *cmd)
{
    int	i;
    int	c;

    c = 0;
    i = 0;
    if (!cmd)
        return (1);
    while (cmd[c])
    {
        if (cmd[c] <= 32)
            i++;
        c++;
    }
    if (i == ft_strlen(cmd))
        return (1);
    return (0);
}