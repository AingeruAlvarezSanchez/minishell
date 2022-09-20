#include "../../include/minishell.h"

/**
 * @param cmd struct with command
 * @param n is -n flag
 */
static void	ft_exec_echo(t_cmd *cmd, int n)
{
	int	x;

	if (cmd->cmd[n])
	{
		while (cmd->cmd[++n])
		{
			x = -1;
			while (cmd->cmd[n][++x])
				write(1, &cmd->cmd[n][x], 1);
			if (cmd->cmd[n + 1])
				write(1, " ", 1);
		}
	}
	g_exit_status = 0;
}

/**
 * @brief check echo argument -n
 * @param cmd struct with command
 */
void	ft_echo(t_cmd *cmd)
{
	int	c;

    c = 1;
	if (cmd->cmd[1] && !ft_strncmp(cmd->cmd[1], "-n", 2))
	{
		while (cmd->cmd[1][++c])
		{
			if (cmd->cmd[1][c] != 'n')
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
