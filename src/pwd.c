#include "../inc/minishell.h"

void	ft_pwd(void)
{
	char	*route;
	route = getcwd(NULL, 0);
	printf("%s\n", route);
	free(route);
	exit(0);
}

