#include "../../include/minishell.h"

void	ft_env(t_env *msh, t_cmd *command)
{
	int	i;

	if (!command->cmd[1])
	{
		i = -1;
		while (msh->env[++i])
			printf("%s\n", msh->env[i]);
		g_exit_status = 0;
	}
	else
	{
		printf("env: %s: No such file or directory\n", command->cmd[1]);
		g_exit_status = 1;
	}
}
