/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 11:41:00 by aalvarez          #+#    #+#             */
/*   Updated: 2021/09/26 11:54:08 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	tmp = NULL;
	if (lst && del)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			del((*lst)->content);
			free (*lst);
			*lst = tmp;
		}
		lst = NULL;
	}
}
