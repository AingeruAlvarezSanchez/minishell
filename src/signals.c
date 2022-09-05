/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:40:09 by aalvarez          #+#    #+#             */
/*   Updated: 2022/09/04 21:57:33 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_signal_exit(t_data *data, t_cmds *cmds)
{
	free(cmds->prompt);
	ft_doublefree(data->env);
	write(1, "exit\n", 5);
	exit(0);
}
