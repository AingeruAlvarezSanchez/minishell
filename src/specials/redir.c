#include "../../include/minishell.h"

bool	ft_has_redir(char *command)
{
	if (ft_str_has(command, "<<"))
		return (true);
	if (ft_str_has(command, ">>"))
		return (true);
	if (ft_str_has(command, "<"))
		return (true);
	if (ft_str_has(command, ">"))
		return (true);
	return (false);
}

