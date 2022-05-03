/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:59:52 by ecorreia          #+#    #+#             */
/*   Updated: 2022/05/03 18:15:56 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/**
 * @brief Function to delete char from string
 * @param str string in witch to search
 * @param delete char to delete
 * @return char* without the chars deleted
 */
char* ft_deletechar(const char* str, const char delete)
{
    char* s;
    int i = -1;
    int sz = 0;
  
    while (str[++i])
        if (ft_strchr(&str[i], delete) == &str[i])
            sz++;
    s = (char*)malloc(i + sz + 1);
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
    s[i] = '\0';
    return s;
}