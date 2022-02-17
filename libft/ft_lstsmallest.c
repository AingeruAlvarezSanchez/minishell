/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsmallest.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:07:10 by aalvarez          #+#    #+#             */
/*   Updated: 2022/01/15 12:08:12 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_lstsmallest(t_list *lst)
{
	int	smallest;

	smallest = (int)lst->content;
	if (!lst)
		return (0);
	while (lst)
	{
		if (smallest > (int)lst->content)
			smallest = (int)lst->content;
		lst = lst->next;
	}
	return (smallest);
}
