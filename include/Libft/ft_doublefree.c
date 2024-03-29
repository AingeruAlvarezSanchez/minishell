/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doublefree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:44:44 by aalvarez          #+#    #+#             */
/*   Updated: 2022/09/21 19:44:44 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
