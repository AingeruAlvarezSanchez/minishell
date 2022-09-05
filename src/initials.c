/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initials.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:22:49 by aalvarez          #+#    #+#             */
/*   Updated: 2022/09/04 20:03:41 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_cpyenv(char **envp, t_data *data)
{
	int	i;

	i = -1;
	g_last_out = 0;
	data->env = (char **)malloc(sizeof(char *) * (ft_doublestrlen(envp) + 1));
	while (envp[++i])
		data->env[i] = ft_strdup(envp[i]);
	data->env[i] = 0;
}

void	ft_initcmds(t_cmds *cmds)
{
	cmds->binary = NULL;
	cmds->command = NULL;
	cmds->n_cmds = 1;
	cmds->token_value = NULL;
	cmds->tokens = NULL;
}
