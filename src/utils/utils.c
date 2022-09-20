#include "../../include/minishell.h"

void	ft_strtolower(char *str)
{
    int		i;

    i = 0;
    while (str && str[i])
    {
        str[i] = ft_tolower(str[i]);
        i++;
    }
}

bool	str_contains(const char *cmd, char *str)
{
	int	i;
	int	u;
	int	length;

	i = 0;
	u = 0;
    length = ft_strlen(str);
	while (cmd[i])
	{
		if (cmd[i] == str[u])
		{
			u++;
			if (u == length)
				return (true);
		}
		else
			u = 0;
		i++;
	}
	return (false);
}

bool	ft_str_has(char *cmd, char *str)
{
    int	i;
    int	u;
    int	maxlength;
    int	mlength;

    i = 0;
    u = 0;
    if (!str || !cmd)
        return (false);
    maxlength = ft_strlen(str);
    mlength = ft_strlen(cmd);
    while (cmd[i])
    {
        if (cmd[i] == str[u])
        {
            u++;
            if (u == maxlength && mlength == maxlength)
                return (true);
        }
        else
            u = 0;
        i++;
    }
    return (false);
}


