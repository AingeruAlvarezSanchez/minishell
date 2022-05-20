/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 05:41:15 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/20 01:34:36 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

static void ft_commands(t_cmds *cmds, t_data *data)
{
    char    *tmp;

    tmp = ft_strtrim(cmds->prompt, " ");
    free(cmds->prompt);
    cmds->prompt = ft_strdup(tmp);
    free(tmp);
    if (!cmds->prompt[0])
        return ;
    ft_initcmds(cmds);
    if (ft_has_special_char(cmds))
    {
        free(cmds->prompt);
        ft_doublefree(cmds->tokens);
        return ;
    }
    ft_dollars(cmds, data);
    int x = -1;
    while (cmds->tokens[++x])
        printf("token: /%s/\n", cmds->tokens[x]);
}

int main(int argc, char **argv, char **envp)
{
    t_cmds  cmds;
    t_data  data;

    ft_cpyenv(envp, &data);
    while (1 && argc && argv)
    {
		cmds.prompt = readline("ejemplo1 ₺ ");
		add_history(cmds.prompt);
        ft_commands(&cmds, &data);
    }
    return (0);
}