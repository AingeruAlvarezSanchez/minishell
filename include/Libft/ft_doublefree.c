#include "libft.h"

void	ft_doublefree(char **str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (str && str[i])
			free(str[i]);
	}
	if (str)
		free(str);
}
