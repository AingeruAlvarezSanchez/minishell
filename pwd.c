#include "minishell.h"

void	ft_pwd()
{
	printf("%s\n", getcwd(NULL, 0));
}

