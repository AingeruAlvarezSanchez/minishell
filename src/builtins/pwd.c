#include "../../include/minishell.h"

/**
 * pwd command
 */
void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
    g_exit = 0;
}
