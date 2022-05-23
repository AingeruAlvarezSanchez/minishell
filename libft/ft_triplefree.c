/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triplefree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 05:59:31 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/21 06:02:32 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_triplefree(char ***str)
{
    int i;

    i = -1;
    while (str[++i])
        ft_doublefree(str[i]);
    free(str);
}
