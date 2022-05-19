/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:13:14 by ecorreia          #+#    #+#             */
/*   Updated: 2022/05/19 18:53:02 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_parser(t_cmds *cmds, char **arr, int cmd_pos)
{
    int i;

    cmds->binary[cmd_pos] = ft_strtrim(arr[0],"\"\'");
    cmds->command[cmd_pos][0] = ft_strdup(cmds->binary[cmd_pos]);
    i = 0;
    while (arr[++i])
        cmds->command[cmd_pos][i] = ft_strtrim(arr[i],"\"\'");
}

void ft_until_pipe(t_cmds *cmds, int n_tkn, int n_comand, char ** tkn)
{
    int i;
    char **arr;// tokens until pipe
        
    arr = (char**)malloc(sizeof(char*) * (n_tkn + 1));
	arr[n_tkn] = 0;
      i = -1;
	while(n_tkn > ++i)
	    arr[i] = ft_strdup(tkn[i]);//guarda tokens hasta pipe
    print_bi_array(arr, "arr");
    cmds->command[n_comand] = (char**)malloc(sizeof(char*) * (n_tkn + 1));
    cmds->command[n_comand][n_tkn] = 0;
    ft_parser(cmds, arr, n_comand);
}

void admin_comands(t_cmds *cmds, char **tkn)
{
	int n_tkn;//token position
	int n_comand; //comand position
    
	n_tkn = 0;
	n_comand = 0;
	while(tkn[n_tkn])
	{
		if(tkn[n_tkn][0] == '|' || !tkn[n_tkn + 1])//encuentra pos de pipe
		{	
            if (!tkn[n_tkn + 1])
            {
                ft_until_pipe(cmds, n_tkn + 1, n_comand, tkn);
                return;
            }
            ft_until_pipe(cmds, n_tkn, n_comand, tkn);
            tkn = tkn + n_tkn + 1;
        	n_tkn = 0;
            n_comand++;   
			continue;
		}
		n_tkn++;
	}
	//ft_doublefree(tkn);
}

void ft_parsing(t_cmds *cmds)
{
    cmds->binary = (char**)malloc(sizeof(char*) * (cmds->n_cmds + 1));
	cmds->binary[cmds->n_cmds] = 0;
    cmds->command = (char***)malloc(sizeof(char**) * (cmds->n_cmds + 1));
	cmds->command[cmds->n_cmds] = 0;
   
	admin_comands(cmds, copy_doble_array(cmds->tokens));
	
	//print_bi_array(cmds->tokens, "tokens");
 	print_bi_array(cmds->binary, "binaries");
    int i = 0;
    while(cmds->command[i])
	    print_bi_array(cmds->command[i++], "comands");
		
}
