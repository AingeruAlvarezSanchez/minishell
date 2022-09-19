#include "../../include/minishell.h"

static void	ft_exec_echo(t_cmd *cmd, int i)
{
	int	x;

	if (cmd->cmd[i])
	{
		while (cmd->cmd[++i])
		{
			x = -1;
			while (cmd->cmd[i][++x])
				write(1, &cmd->cmd[i][x], 1);
			if (cmd->cmd[i + 1])
				write(1, " ", 1);
		}
	}
	g_exit_status = 0;
}

void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->cmd[1] && !ft_strncmp(cmd->cmd[1], "-n", 2))
	{
		while (cmd->cmd[1][++i])
		{
			if (cmd->cmd[1][i] != 'n')
			{
				ft_exec_echo(cmd, 0);
				write(1, "\n", 1);
				return ;
			}
		}
		ft_exec_echo(cmd, 1);
		return ;
	}
	ft_exec_echo(cmd, 0);
	write(1, "\n", 1);
}
