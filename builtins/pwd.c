#include "../minishell.h"

void	ft_pwd(void)
{
	ft_echo(getcwd(NULL, 0), NULL);
}

