#include "libft.h"
#include <stdio.h>

static char	**ft_free(char **p, size_t count)
{
	size_t	i;

	if (p)
	{
		i = 0;
		while (i < count)
		{
			if (p[i] != NULL)
				free(p[i]);
			i++;
		}
		free (p);
	}
	return (NULL);
}

size_t	ft_count_size(char *s, char c)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	if (!s)
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			if (*s && *s == 34 || *s == 39)
				s = ft_skip_quotes_size(s, quote);
			i++;
			while (*s && *s != c)
				s++;
		}	
	}
	return (i);
}

static char	*ft_fill_each_pointer(char *s, char c)
{
	char	*pnt;
	int		i;
	char	quote;

	i = 0;
	while (s[i] && s[i] != c)
	{	
		if (s[i] && s[i] == 34 || s[i] == 39)
		{
			quote = s[i];
			if (s[i + 1])
				i++;
			while (s[i] && s[i] != quote)
				i++;
		}
		i++;
	}
	pnt = (char *)malloc(sizeof(char) * (i + 1));
	if (!pnt)
		return (NULL);
	i = 0;
	pnt = ft_create_pnt(s, quote, pnt, c);
	return (pnt);
}

static char	**ft_fill_pointers(char *s, char c, char **tab)
{
	int		i;
	char	quote;

	i = 0;
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s && *s != c)
		{
			tab[i] = ft_fill_each_pointer(s, c);
			if (!tab[i])
				return (ft_free(tab, i));
			i++;
			s = ft_skipquotes(s, c, quote);
		}
	}
	tab[i] = NULL;
	return (tab);
}

char	**mini_split(char *s, char c)
{
	int		size;
	char	**tab;

	if (s)
		size = ft_count_size(s, c);
	tab = malloc ((size + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab = ft_fill_pointers(s, c, tab);
	return (tab);
}
