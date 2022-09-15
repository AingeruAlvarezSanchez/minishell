#include "../../include/minishell.h"

bool	contains_redire(char *command)
{
	if (str_exactly_contains(command, "<<"))
		return (true);
	if (str_exactly_contains(command, ">>"))
		return (true);
	if (str_exactly_contains(command, "<"))
		return (true);
	if (str_exactly_contains(command, ">"))
		return (true);
	return (false);
}

