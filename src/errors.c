/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:55:57 by aalvarez          #+#    #+#             */
/*   Updated: 2022/09/04 19:18:34 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

int	ft_pipes_error(t_cmds *cmds, int xref, int check)
{
	if (!cmds->prompt[xref + 1] || cmds->prompt[xref + 1] == '|'
		|| (xref == 0 && check != 1))
		return (printf("Syntax error near unexpected token '|'\n"), 1);
	return (0);
}

int	ft_has_final(t_cmds *cmds, int xref, char c)
{
	while (cmds->prompt[++xref])
	{
		if (cmds->prompt[xref] == c)
			return (1);
	}
	printf("Syntax error, one or more quotes are not closed\n");
	return (0);
}
