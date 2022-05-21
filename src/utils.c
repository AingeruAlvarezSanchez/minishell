/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:33:33 by ecorreia          #+#    #+#             */
/*   Updated: 2022/05/21 01:46:15 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void print_bi_array(char **arr, char *text)
{
	int y;

	y = 0;
	if(!arr && !arr[0][0])
		return;
	while(arr[y] && arr[y][0])
	{
		if(arr[y][0])
			{printf("%d.%s->%s.\n", y + 1, text, arr[y]);
			y++;}
	}
}
