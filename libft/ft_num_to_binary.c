/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_to_binary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:49:13 by aalvarez          #+#    #+#             */
/*   Updated: 2022/02/17 17:29:52 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_num_to_binary(int num)
{
	char	*str;
	int		i;
	int		content;
	int		result;

	i = 1;
	content = num;
	while (content / 2 != 0 || content / 2 != 1)
	{
		if (content / 2 == 0 || content / 2 == 1)
			break ;
		content = content / 2;
		i++;
	}
	i++;
	str = (char *)malloc(sizeof(char) * i);
	content = num;
	while (i--)
	{
		str[i] = content % 2 + 48;
		content = content / 2;
	}
	result = ft_atoi(str);
	free (str);
	return (result);
}
