/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initials.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:29:04 by aalvarez          #+#    #+#             */
/*   Updated: 2022/03/31 21:29:04 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* This function is used to create a copy of the environment in the data structure */
void	ft_cpyenv(t_data *data, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	data->env = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		data->env[i] = ft_strdup(envp[i]);
	data->env[i] = 0;
}

 /* This function is used to create a copy of the PATH variable onto the data structure */
void	ft_get_path(t_data *data)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (ft_strncmp(data->env[i], "PATH=", 5))
		i++;
	tmp2 = ft_strtrim(data->env[i], "PATH=");
	data->path = ft_split(tmp2, ':');
	i = 0;
	while (data->path[i])
	{
		tmp = ft_strjoin(data->path[i], "/");
		free(data->path[i]);
		data->path[i] = tmp;
		i++;
	}
	free (tmp2);
	free (tmp);
}

/* A function to make sure every non already initialized structure component is indeed initalized */
void	ft_initials(t_cmds *cmds, t_data *data, char *prompt)
{
	cmds->tokens = (char **)malloc(sizeof(char *) * 2);
	cmds->tokens[0] = ft_strdup(prompt);
	cmds->tokens[1] = 0;
	data->last_out = 0;
	cmds->n_cmds = 1;
}
