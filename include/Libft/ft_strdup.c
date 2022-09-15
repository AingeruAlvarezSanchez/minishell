/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:22:14 by aalvarez          #+#    #+#             */
/*   Updated: 2022/03/29 22:06:17 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strdup(const char *s1)
{
	char	*s;
	int		i;

	s = (char *)malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (!s)
		return (NULL);
	i = -1;
	while (s1[++i])
		s[i] = s1[i];
	s[i] = 0;
	return (s);
}
