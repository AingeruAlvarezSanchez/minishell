/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:38:47 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/29 00:18:43 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_data *Data)
{
	int	i;
	int	j;

	i = -1;
	while (Data->env[++i])
	{
		j = -1;
		while (Data->env[i][++j])
			write(1, &Data->env[i][j], 1);
		write(1, "\n", 1);
		Data->last_out = 0;
	}
	exit(0);
}
