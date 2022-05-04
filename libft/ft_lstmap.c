/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 11:44:47 by aalvarez          #+#    #+#             */
/*   Updated: 2021/09/26 12:11:15 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*to_add;

	if (!lst || !f)
		return (0);
	head = NULL;
	while (lst)
	{
		to_add = ft_lstnew((*f)(lst->content));
		if (!to_add)
		{
			ft_lstclear(&head, del);
			return (0);
		}
		ft_lstadd_back(&head, to_add);
		lst = lst->next;
	}
	return (head);
}
