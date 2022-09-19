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

static int	get_position(int i, char *raw_cmd)
{
	int	x;

	while (++i < ft_strlen(raw_cmd))
	{
		if (raw_cmd[i] == '\'' || raw_cmd[i] == '"')
		{
			x = i + 1;
			while (raw_cmd[x])
			{
				if (raw_cmd[x] == raw_cmd[i])
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

int	ft_process_quotes(char *raw_cmd)
{	
	int		i;

	i = -1;
	if (!raw_cmd)
        raw_cmd = NULL;
	if (get_position(i, raw_cmd))
		return (true);
	return (false);
}
