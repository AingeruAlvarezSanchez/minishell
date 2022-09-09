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

void	ft_init_execute(t_cmds *cmds, int pos)
{
    if (cmds->n_cmds != 1)
    {
        if (pos == 0)
        {
            if (cmds->n_cmds > 2)
                dup2(cmds->pipefd[1][WRITE], STDOUT_FILENO);
            else
                dup2(cmds->pipefd[0][WRITE], STDOUT_FILENO);
        }
        else if (pos != 0 && pos != cmds->n_cmds - 1)
        {
            dup2(cmds->pipefd[1][WRITE], STDOUT_FILENO);
            dup2(cmds->pipefd[0][READ], STDIN_FILENO);
        }
        else if (pos == cmds->n_cmds - 1)
            dup2(cmds->pipefd[0][READ], STDIN_FILENO);
    }
}

void	ft_createpaths(t_data *data)
{
    int		i;
    char	**tmp;

    i = -1;
    while (data->env[++i])
    {
        if (!ft_strncmp(data->env[i], "PATH=", 5))
        {
            tmp = ft_split(data->env[i], ':');
            i = -1;
            data->paths = (char **)malloc(sizeof(char *)
                                          * (ft_doublestrlen(tmp) + 1));
            while (tmp[++i])
                data->paths[i] = ft_strjoin(tmp[i], "/");
            data->paths[i] = 0;
            ft_doublefree(tmp);
            break ;
        }
    }
    data->export_env = ft_doublestrdup(data->env);
}


void	ft_cpyenv(char **envp, t_data *data)
{
	int	i;

	i = -1;
	data->g_last_out = 0;
	data->env = (char **)malloc(sizeof(char *) * (ft_doublestrlen(envp) + 1));
	while (envp[++i])
		data->env[i] = ft_strdup(envp[i]);
	data->env[i] = 0;
    ft_createpaths(data);//TODO: update path
}

void	ft_initcmds(t_cmds *cmds)
{
	cmds->binary = NULL;
	cmds->command = NULL;
	cmds->n_cmds = 1;
	cmds->token_value = NULL;
	cmds->tokens = NULL;
    cmds->pid = getpid();
}
