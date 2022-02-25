#include "minishell.h"

void	ft_echo(char *str,__attribute__((unused)) char *flag)
{
	int	i;

	i = -1;
	while(str[++i])
		write(1, &str[i], 1);
	write(1, "\n", 1);
	exit(0);
}

