/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:29:19 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/23 19:46:40 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

int	ft_has_final(t_cmds *cmds, int xref, char c)
{
	while (cmds->prompt[++xref])
	{
		if (cmds->prompt[xref] == c)
			return (1);
	}
	printf("Syntax error, one ore more quotes are not closed\n");
	return (0);
}

int	ft_pipes_error(char *prompt, char *sp)
{
	if (!*prompt/* || ft_nomorecommand(cmds, iref, jref)*/)
	{
		printf("Syntax error near unexpected token '%c'\n", sp[0]);
		return (1);
	}
	while (*prompt == ' ')
		prompt++;
	if (ft_is_pipe_or_redir(*prompt))
	{
		while (*prompt == ' ')
			prompt++;
		if (ft_is_pipe_or_redir(*prompt))
		{
			printf("Syntax error near unexpected token '%c'\n", sp[0]);
			return (1);
		}
	}
	return (0);
}