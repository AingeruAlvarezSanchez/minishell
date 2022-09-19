#include "../../include/minishell.h"

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


bool	ft_str_has(char *command, char *str)
{
    int	i;
    int	u;
    int	maxlength;
    int	mlength;

    i = 0;
    u = 0;
    if (!str || !command)
        return (false);
    maxlength = ft_strlen(str);
    mlength = ft_strlen(command);
    while (command[i])
    {
        if (command[i] == str[u])
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


void	string_to_lower(char *pnt)
{
	int		i;
	char	c;

	i = 0;
	while (pnt && pnt[i])
	{
        c = ft_tolower(pnt[i]);
		pnt[i] = c;
		i++;
	}
}
