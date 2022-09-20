#include "../../include/minishell.h"

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
		g_exit_status = 0;
	}
	else
	{
		printf("env: %s: No such file or directory\n", cmd->cmd[1]);
		g_exit_status = 1;
	}
}
