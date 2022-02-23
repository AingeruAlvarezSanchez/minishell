#include "../minishell.h"

void	ft_echo(char *str, char *flag)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
	if (flag == "-n")
		return ;
	else
		write(1, "\n", 1);
}

