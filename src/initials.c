/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initials.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 07:44:17 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/18 19:51:18 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void    ft_createpaths(t_data *data)
{
    int     i;
    char    **tmp;

    i = -1;
    while (data->env[++i])
    {
        if (!ft_strncmp(data->env[i], "PATH=", 5))
        {
            tmp = ft_split(data->env[i], ':');
            i = -1;
            data->paths = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) + 1));
            while (tmp[++i])
                data->paths[i] = ft_strjoin(tmp[i], "/");
            data->paths[i] = 0;
            ft_doublefree(tmp);
            break ;
        }
    }
}

void    ft_cpyenv(char **envp, t_data *data)
{
    int i;

    i = -1;
    data->env = (char **)malloc(sizeof(char *) * (ft_doublestrlen(envp) + 1));
    while (envp[++i])
        data->env[i] = ft_strdup(envp[i]);
    data->env[i] = 0;
    ft_createpaths(data);
}

void ft_initcmds(t_cmds *cmds)
{
    cmds->tokens = (char **)malloc(sizeof(char *));
    cmds->tokens[0] = 0;

    cmds->n_cmds = 1;

    cmds->pipefd = (int **)malloc(sizeof(int *) * 2);
	cmds->pipefd[0] = (int *)malloc(sizeof(int) * 2);
	cmds->pipefd[1] = (int *)malloc(sizeof(int) * 2);

}