#include "../../include/minishell.h"

bool	check_if_empty_command(char *str)
{
	int	i;
	int	length;
	int	u;

	i = 0;
	u = 0;
	if (!str)
		return (true);
	length = ft_strlen(str);
	while (str[i])
	{
		if (str[i] <= 32)
			u++;
		i++;
	}
	if (u == length)
		return (true);
	return (false);
}

static int	get_position(int i, char *not_processed_cmd)
{
	int	x;

	x = 0;
	while (++i < ft_strlen(not_processed_cmd))
	{
		if (not_processed_cmd[i] == '\'' || not_processed_cmd[i] == '"')
		{
			x = i + 1;
			while (not_processed_cmd[x])
			{
				if (not_processed_cmd[x] == not_processed_cmd[i])
				{
					i = x;
					break ;
				}
				x++;
			}
			if (i == x)
				continue ;
			return (true);
		}
	}
	return (false);
}

int	process_string_quotes(char *not_processed_cmd)
{	
	int		i;

	i = -1;
	if (!not_processed_cmd)
		not_processed_cmd = NULL;
	if (get_position(i, not_processed_cmd))
		return (true);
	return (false);
}
