/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:38:38 by ecorreia          #+#    #+#             */
/*   Updated: 2022/09/21 19:38:38 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_strtolower(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		str[i] = (char)ft_tolower(str[i]);
		i++;
	}
}

bool	ft_str_contains(const char *cmd, char *str)
{
	int	i;
	int	u;
	int	length;

	i = 0;
	u = 0;
	length = ft_strlen(str);
	while (cmd[i])
	{
		if (cmd[i] == str[u])
		{
			u++;
			if (u == length)
				return (true);
		}
		else
			u = 0;
		i++;
	}
	return (false);
}

bool	ft_str_has(char *cmd, char *str)
{
	int	i;
	int	u;
	int	maxlength;
	int	mlength;

	i = 0;
	u = 0;
	if (!str || !cmd)
		return (false);
	maxlength = ft_strlen(str);
	mlength = ft_strlen(cmd);
	while (cmd[i])
	{
		if (cmd[i] == str[u])
		{
			u++;
			if (u == maxlength && mlength == maxlength)
				return (true);
		}
		else
			u = 0;
		i++;
	}
	return (false);
}

char	*ft_cpy_path(t_cmd *cmd, int pos)
{
	char	*path;

	path = ft_strdup(cmd->path[pos]);
	ft_doublefree(cmd->path);
	return (path);
}

/**
 *
 * @param cmds struct with commands
 * @param pos_cmd actual position of command
 * @param n_cmd number of commands in prompt
 * @param env struct with environment
 * @return 1
 */
bool	ft_final_cmd(t_cmds_all *cmds, int pos_cmd, int n_cmd, t_env *env)
{
	ft_is_exit(cmds, pos_cmd, n_cmd);
	ft_parent_builtin(&cmds->cmds[pos_cmd], env, n_cmd, pos_cmd);
	ft_free_commands(cmds);
	return (1);
}
