/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:33:33 by ecorreia          #+#    #+#             */
/*   Updated: 2022/05/11 18:34:07 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <stdlib.h>

char **copy_doble_array(char **arr)
{
	char **new;
	int i;
	
	i = 0;
	while(arr[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 1));
	new[i] = 0;
	i = 0;
	while(arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	return new;
}

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