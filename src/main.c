/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 22:56:10 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/06 00:40:43 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * @brief When there is only one command, this function
 * creates a 2 spaces double array and allocates the 
 * prompt and a NULL spot
 */
void	ft_mono_command(t_cmds *cmds, char* prompt)
{
	int		i;
    
    i = 0;
    while (cmds->tokens[0][i] && cmds->tokens[0][i] == ' ')//por si hay espacios delante
        i++;    
    
    cmds->binary = (char**)malloc(sizeof(char*) * cmds->n_cmds); // vale para mono o varios
    cmds->flags = (char**)malloc(sizeof(char*) * cmds->n_cmds);
    cmds->command = (char**)malloc(sizeof(char*) * cmds->n_cmds);
    
    if (cmds->tokens[0][i] == '"' || cmds->tokens[0][i] == '\'')//lo que esta entre commilas es comando
    {
        while (cmds->tokens[0][++i])
            if(cmds->tokens[0][i] == '"' || cmds->tokens[0][i] == '\'')
                cmds->binary[0] = ft_substr(ft_strtrim(cmds->tokens[0], "\""), 0, i);
                
        if(prompt[ft_strlen(cmds->tokens[0])] == ' ')
        {
             cmds->flags[0] = ft_strjoin(" ", cmds->tokens[1]);
            cmds->command[0] = ft_strjoin(cmds->binary[0], cmds->flags[0]);
        }       
        else
            if(cmds->tokens[1])
            {
                cmds->flags[0] = ft_strdup(cmds->tokens[1]);
             // si esta despues de comillas es flag fijo  
              cmds->command[0] = ft_strjoin(cmds->binary[0], cmds->flags[0]);
            }
            else
                cmds->command[0] = ft_strdup(cmds->binary[0]);
            
    }
    else
    {
        while(cmds->tokens[0][i] && cmds->tokens[0][i] != ' ')
            i++;
        cmds->binary[0] = ft_substr(cmds->tokens[0], 0, i);  
        cmds->flags[0] = ft_substr(cmds->tokens[0], i, ft_strlen(cmds->tokens[0]) - i);
        cmds->command[0] = ft_strjoin(cmds->binary[0], cmds->flags[0]);
    }

    
    printf("token1--->%s.\n", cmds->tokens[0]);
    if (cmds->tokens[1])
        printf("token2--->%s.\n", cmds->tokens[1]);
    if (cmds->binary[0])    
        printf("binary-->%s.\n", cmds->binary[0]);
    //if (cmds->flags && cmds->flags[0])
    //    printf("flag---->%s.\n", cmds->flags[0]);
    if (cmds->command[0])
        printf("comand-->%s.\n", cmds->command[0]);
}

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
    if (cmds->n_cmds == 1)
        ft_mono_command(cmds, prompt);
    
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