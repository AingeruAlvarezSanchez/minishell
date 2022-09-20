#include "libft.h"

int	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		i++;
	}
	return (i);
}
