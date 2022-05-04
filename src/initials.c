/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initials.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 23:08:33 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/04 03:41:26 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void    ft_create_paths(t_data *data)
{
    int     i;
    char    **tmp;

    i = -1;
    while (data->env[++i])
    {
        if (!ft_strncmp(data->env[i], "PATH=", 5))
            break ;
    }
    tmp = ft_split(data->env[i], ':');
    data->paths = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) + 1));
    i = -1;
    while (tmp[++i])
        data->paths[i] = ft_strjoin(tmp[i], "/");
    data->paths[i] = 0;
    ft_doublefree(tmp);
}

void    ft_cpyenv(t_data *data, char **envp)
{
    int i;

    i = -1;
    data->env = (char **)malloc(sizeof(char *) * (ft_doublestrlen(envp) + 1));
    while (envp[++i])
        data->env[i] = ft_strdup(envp[i]);
    data->env[i] = 0;
    ft_create_paths(data);
}

void ft_initcmds(char *prompt, t_cmds *cmds)
{
    cmds->tokens = (char **)malloc(sizeof(char *) * 2);
    cmds->tokens[0] = ft_strdup(prompt);
    cmds->tokens[1] = 0;
    cmds->n_cmds = 1;
}
