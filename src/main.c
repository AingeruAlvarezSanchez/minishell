/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 22:56:10 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/06 18:03:55 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>



static void ft_commands(char *prompt, t_data *data, t_cmds *cmds/*, t_proc *proc*/)
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

    ft_parsing(cmds, prompt);
    
    ft_doublefree(cmds->tokens);
    //if (!cmds->command[0][0])
	//	return ;
	//ft_check_builtins(cmds, data);
}

int main(int argc, char **argv, char **envp)
{
    char		*prompt;
	t_cmds		cmds;
	t_data		data;
	//t_proc      proc;

	ft_cpyenv(&data, envp);
	/*ft_interactive(1);
	ft_signals();*/
	while (1 && argc && argv)
	{
		prompt = readline("ejemplo1 ₺ ");
		add_history(prompt);
		ft_commands(prompt, &data, &cmds/*, &proc*/);
		//waitpid(cmds.pid, NULL, WUNTRACED);
        free(prompt);
	}
	return (0);
    
}