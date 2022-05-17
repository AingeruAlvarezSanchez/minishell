/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doublestrdup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:34:55 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/16 06:11:25 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char **ft_doublestrdup(char **str)
{
    char    **result;
    int     i;

    i = -1;
    result = (char **)malloc(sizeof(char *) * (ft_doublestrlen(str) + 1));
    if (!result)
        return (NULL);
    while (str[++i])
        result[i] = ft_strdup(str[i]);
    result[i] = 0;
    ft_doublefree(str);
    return (result);
}