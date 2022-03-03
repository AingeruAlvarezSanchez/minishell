#include "../inc/minishell.h"

void	ft_env(t_data *Data)
{
	int	i;
	int	j;

	i = -1;
	while (Data->env[++i])
	{
		j = -1;
		while (Data->env[i][++j])
			write(1, &Data->env[i][j], 1);
		write(1, "\n", 1);
	}
	exit(0);
}

