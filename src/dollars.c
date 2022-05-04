/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 05:09:56 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/04 05:13:54 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

void ft_check_dollar(t_cmds *cmds,__attribute__((unused)) t_data *data, int iref, int jref)
{
	if (!cmds->tokens[iref][jref + 1])
		return ;
	//if (cmds->tokens[iref][jref + 1] == '?')
		//ft_last_status();
}