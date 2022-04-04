/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 08:37:11 by aalvarez          #+#    #+#             */
/*   Updated: 2022/04/04 08:53:41 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief This function checks wheter the builtins created
 * is a parent or a child builtin
 * 
 * @return int If the funcion successes on finding any of the
 * parent builtin names it returns true so the calling function
 * can determine what handler to use
 */
int	ft_check_parent(t_cmds *cmds)
{
	if (!ft_strncmp(cmds->proccess[0], "exit", 4) && !cmds->proccess[0][4])
		return (1);
	else if (!ft_strncmp(cmds->proccess[0], "cd", 2) && !cmds->proccess[0][2])
		return (1);
	else if (!ft_strncmp(cmds->proccess[0], "export", 6) && !cmds->proccess[0][6])
		return (1);
	else if (!ft_strncmp(cmds->proccess[0], "unset", 5) && !cmds->proccess[0][5])
		return (1);
	return (0);
}

/**
 * @brief If the check_parent function returns true, this function
 * is called in order to check what builtin should be called for 
 * execution
 * 
 * @param cmd_n This is the actual executing command number in
 * all the commands sent by pipes
 */
void	ft_parent_builtin(t_cmds *cmds, t_data *data, int cmd_n)
{
	if (!ft_strncmp(cmds->proccess[0], "exit", 4) && !cmds->proccess[0][4])
		ft_exit(cmds, data, cmd_n);
	else if (!ft_strncmp(cmds->proccess[0], "cd", 2) && !cmds->proccess[0][2])
		ft_cd(cmds, data, cmd_n);
	else if (!ft_strncmp(cmds->proccess[0], "export", 6) && !cmds->proccess[0][6])
        ft_check_export(cmds, data, cmd_n);
	else if (!ft_strncmp(cmds->proccess[0], "unset", 5) && !cmds->proccess[0][5])
        ft_check_unset(cmds, data, cmd_n);
}
