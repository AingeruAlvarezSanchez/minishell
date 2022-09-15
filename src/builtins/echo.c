#include "../../include/minishell.h"

static void	ft_exec_echo(t_command *command, int start)
{
	int	x;

	if (command->command[start])
	{
		while (command->command[++start])
		{
			x = -1;
			while (command->command[start][++x])
				write(1, &command->command[start][x], 1);
			if (command->command[start + 1])
				write(1, " ", 1);
		}
	}
	g_exit_status = 0;
}

void	ft_echo(t_command *command)
{
	int	i;

	i = 1;
	if (command->command[1] && !ft_strncmp(command->command[1], "-n", 2))
	{
		while (command->command[1][++i])
		{
			if (command->command[1][i] != 'n')
			{
				ft_exec_echo(command, 0);
				write(1, "\n", 1);
				return ;
			}
		}
		ft_exec_echo(command, 1);
		return ;
	}
	ft_exec_echo(command, 0);
	write(1, "\n", 1);
}
