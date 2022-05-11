/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 04:27:25 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/11 21:10:36 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

#define start	NULL
#define end		NULL

/**
 * @brief Once every separator or metacharacter has been
clasified, this function creates the definitive version
of the commands separated by pipes
 */
void	ft_parser(t_cmds *cmds, char **arr, int cmd_pos)
{
	int		i;
    //(void) prompt;
	
    i = 0;
    while (arr[0][i] && arr[0][i] == ' ')//por si hay espacios delante
        i++;
    if (arr[0][i] == '\"' || arr[0][i] == '\'')//lo que esta entre commilas es comando
    {
        while (arr[0][++i])
			if(arr[0][i] == '\"' || arr[0][i] == '\'')
                cmds->binary[cmd_pos] = ft_substr(ft_strtrim(arr[0], "\""), 0, i); //elimina comillas
			if(arr[1])//si hay flag
			{
				cmds->flags[cmd_pos] = ft_strtrim(arr[1], "\"");// si esta despues de comillas es flag fijo 
				cmds->command[cmd_pos] = ft_strjoin(cmds->binary[cmd_pos], cmds->flags[cmd_pos]);
			}
			else
			{
				cmds->flags[cmd_pos] = 0;
				cmds->command[cmd_pos] = ft_strdup(cmds->binary[cmd_pos]);      
			}    
    }
    else
    {	
		while(arr[0][i] && arr[0][i] != ' ')
            i++;
        cmds->binary[cmd_pos] = ft_substr(arr[0], 0, i++);  
		if((int)ft_strlen(arr[0]) - i > 0)
		{
        	cmds->flags[cmd_pos] = ft_substr(arr[0], i, ft_strlen(arr[0]) - i);
        	cmds->command[cmd_pos] = ft_strjoin(cmds->binary[cmd_pos], ft_strjoin(cmds->flags[cmd_pos], " "));
		}
		else
		{
			cmds->flags[cmd_pos] = 0; 
			cmds->command[cmd_pos] = ft_strdup(cmds->binary[cmd_pos]);
		}         
    }
}

void admin_comands(t_cmds *cmds, char **tkn)
{
	int n_tkn;//token position
	int i;
	char **arr;// tokens until pipe
	int n_comand; //comand position
	
	n_tkn = 0;
	n_comand = 0;
	while(tkn[n_tkn])
	{
		if(tkn[n_tkn][0] == '|' || !tkn[n_tkn + 1] )//encuentra pos de pipe
		{	
			if(!tkn[n_tkn + 1])//si es el ultimo
				n_tkn++;
			arr = (char**)malloc(sizeof(char*) * (n_tkn + 1));
			arr[n_tkn] = 0;
			i = -1;
			while(n_tkn > ++i)
				arr[i] = ft_strdup(tkn[i]);//guarda tokens hasta pipe

			if (cmds->n_cmds > 1)
				ft_parser(cmds, arr, n_comand);
			else if(cmds->n_cmds == 1)
				ft_parser(cmds, arr, 0);
			else
				return ;
			ft_doublefree(arr);
			if(tkn[0 + n_tkn] ) 
				tkn = tkn + n_tkn;//avanza en puntero los tokens hasta pipe
			else
				return;
			n_tkn = 0;
			if(tkn[0][0] == '|')
				tkn++;
			n_comand++;
			continue;
		}
		n_tkn++;
	}
	ft_doublefree(tkn);
}

void ft_parsing(t_cmds *cmds)
{
    cmds->binary = (char**)malloc(sizeof(char*) * (cmds->n_cmds + 1));
	cmds->binary[cmds->n_cmds] = 0;
    cmds->flags = (char**)malloc(sizeof(char*) * (cmds->n_cmds + 1));
	cmds->flags[cmds->n_cmds] = 0;
    cmds->command = (char**)malloc(sizeof(char*) * (cmds->n_cmds + 1));
	cmds->command[cmds->n_cmds] = 0;
	cmds->after_cmd = (char *)malloc(sizeof(char) * cmds->n_cmds);

	admin_comands(cmds, copy_doble_array(cmds->tokens));
	
	print_bi_array(cmds->tokens, "tokens");
 	print_bi_array(cmds->binary, "binaries");
   	print_bi_array(cmds->flags, "flags");
	print_bi_array(cmds->command, "comands");
		
}