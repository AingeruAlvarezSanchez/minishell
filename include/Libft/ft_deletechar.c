/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletechar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 03:24:08 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/06 20:49:22 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_deletechar(const char *str, const char delete)
{
	char	*s;
	int		i;
	int		sz;

	i = -1;
	sz = 0;
	while (str[++i])
	{
		if (ft_strchr(&str[i], delete) == &str[i])
			sz++;
	}
	s = (char *)malloc(i + sz + 1);
	i = 0;
	while (*str)
	{
		if (ft_strchr(str, delete) == str)
		{
			ft_strlcpy(&s[i], "", 0);
			str += 1;
		}
		else
			s[i++] = *str++;
	}
	s[i] = 0;
	return (s);
}
