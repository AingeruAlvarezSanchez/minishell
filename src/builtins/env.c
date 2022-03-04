/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:38:47 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/03 18:39:01 by ecorreia         ###   ########.fr       */
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
	}
	exit(0);
}