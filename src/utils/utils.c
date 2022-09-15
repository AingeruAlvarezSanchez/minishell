#include "../../include/minishell.h"

bool	str_contains(char *command, char *str)
{
	int	i;
	int	u;
	int	maxlength;

	i = 0;
	u = 0;
	maxlength = ft_strlen(str);
	while (command[i])
	{
		if (command[i] == str[u])
		{
			u++;
			if (u == maxlength)
				return (true);
		}
		else
			u = 0;
		i++;
	}
	return (false);
}


bool	str_exactly_contains(char *command, char *str)
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
	char	aux;

	i = 0;
	while (pnt && pnt[i])
	{
		aux = ft_tolower(pnt[i]);
		pnt[i] = aux;
		i++;
	}
}
