#include "../../include/minishell.h"

bool	ft_check_variable(char *variable)
{
	int	i;

	i = -1;
	while (variable[++i])
	{
		if (variable[i] == '=')
			return (false);
	}
	return (true);
}

bool	ft_already_in(char *variable, char **env)
{
	int		i;
	char	*to_search;

	i = 0;
	while (variable[i] != '=')
		i++;

	to_search = ft_substr(variable, 0, (i + 1));
	while (env[++i])
	{
		if (!ft_strncmp(env[i], to_search, ft_strlen(to_search)))
		{
			free(to_search);
			return (true);
		}
	}
	free(to_search);
	return (false);
}
