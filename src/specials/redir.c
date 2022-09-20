#include "../../include/minishell.h"

/**
 * @param cmd string with cmd
 * @return true if has redir
 */
bool	ft_has_redir(char *cmd)
{
	if (ft_str_has(cmd, "<<"))
		return (true);
	if (ft_str_has(cmd, ">>"))
		return (true);
	if (ft_str_has(cmd, "<"))
		return (true);
	if (ft_str_has(cmd, ">"))
		return (true);
	return (false);
}

