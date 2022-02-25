#include "minishell.h"

void	ft_echo(char *str, char *flag)
{
	int	i;

	if (!str)
	{
		write(1, "\n", 1);
		exit(0);
	}
	i = -1;
	while(str[++i])
		write(1, &str[i], 1);
	if (flag)
		exit(0);
	write(1, "\n", 1);
	exit(0);
}

void	ft_check_echo(t_cmds *Cmds)
{
	if (!Cmds->p_command[1])
	{
		write(1, "\n", 1);
		exit(0);
	}
	else if (!ft_strncmp(Cmds->p_command[1], "-n", 2))
		ft_echo(Cmds->p_command[2], Cmds->p_command[1]);
	else
		ft_echo(Cmds->p_command[1], NULL);
}

