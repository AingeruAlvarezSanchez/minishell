/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:48:36 by ecorreia          #+#    #+#             */
/*   Updated: 2022/09/21 19:48:36 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_check_access(t_cmds_all *cmds, int pos_cmd)
{
	if (access(cmds->cmds[pos_cmd].cmd[0], X_OK) == 0)
	{
		cmds->cmds[pos_cmd].bin_pth
			= ft_strdup(cmds->cmds[pos_cmd].cmd[0]);
		cmds->cmds[pos_cmd].absolute = true;
		return (true);
	}
	return (false);
}

void	ft_free_exec(t_cmds_all *cmds)
{
	int	cmd;

	cmd = -1;
	close(cmds->sngl_pipe);
	if (cmds->n_cmds > 1)
		free(cmds->pipes);
	ft_free_commands(cmds);
}

/**
 * @brief free dollar struct
 */
void	ft_struct_free(t_dollar *dollar)
{
	free(dollar->pre);
	free(dollar->final);
	free(dollar->val);
	free(dollar->result);
}
