/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 22:56:10 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/04 05:12:28 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

static void ft_commands(char *prompt, t_data *data, t_cmds *cmds)
{
    if (!prompt[0])
        return ;
    ft_initcmds(prompt, cmds);
    if (ft_has_special_char(cmds))
    {
        ft_doublefree(cmds->tokens);
		return ;
    }
    ft_check_metacharacter(cmds, data);
    int i = -1;
    while (cmds->tokens[++i])
    {
        printf("token: /%s/\n", cmds->tokens[i]);
    }
    ft_doublefree(cmds->tokens);
}

int main(int argc, char **argv, char **envp)
{
    char		*prompt;
	t_cmds		cmds;
	t_data		data;
	//t_command	command;

	ft_cpyenv(&data, envp);
	/*ft_interactive(1);
	ft_signals();*/
	while (1 && argc && argv)
	{
		prompt = readline("ejemplo1 ₺ ");
		add_history(prompt);
		ft_commands(prompt, &data, &cmds);
		//waitpid(cmds.pid, NULL, WUNTRACED);
        free(prompt);
	}
	return (0);
    
}