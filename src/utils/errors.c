/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:59:05 by ecorreia          #+#    #+#             */
/*   Updated: 2022/09/21 18:59:05 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_print_err(int error)
{
	if (error == 5)
	{
		fprintf(stderr, "ERR : QUOTATION\n");
		return (1);
	}
	else if (error == 9)
	{
		fprintf(stderr, "ERR: Command not found\n");
		return (1);
	}
	else if (error == 8)
	{
		fprintf(stderr, "ERR : FINAL PIPE\n");
		return (1);
	}
	else if (error == 12)
	{
		fprintf(stderr, "ERR : EMPTY PIPE\n");
		return (1);
	}
	return (0);
}

void	ft_free_commands(t_cmds_all *cmds)
{
	int	i;

	i = -1;
	while (++i < cmds->n_cmds && cmds->n_cmds)
	{
		if (cmds->cmds[i].cmd)
			ft_doublefree(cmds->cmds[i].cmd);
		cmds->cmds[i].cmd = NULL;
		if (cmds->cmds[i].bin_pth)
		{
			free(cmds->cmds[i].bin_pth);
		}
		cmds->cmds[i].bin_pth = NULL;
	}
	if (!cmds->cmds)
		return ;
	free(cmds->cmds);
}

bool	ft_check_errors(char *prompt)
{
	prompt = ft_pipe_add(prompt);
	if (prompt == NULL || (ft_strlen(prompt) <= 0))
	{
		if (prompt)
			free(prompt);
		return (1);
	}	
	return (0);
}
