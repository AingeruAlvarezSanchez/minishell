#include "../../include/minishell.h"

void	ft_env(t_msh_var *msh, t_command *command)
{
	int	i;

	if (!command->command[1])
	{
		i = -1;
		while (msh->own_envp[++i])
			printf("%s\n", msh->own_envp[i]);
		g_exit_status = 0;
	}
	else
	{
		printf("env: %s: No such file or directory\n", command->command[1]);
		g_exit_status = 1;
	}
}
