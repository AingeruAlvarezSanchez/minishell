/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 04:27:25 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/09 22:10:36 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

/**
 * @brief This function creates a new double array containing
 * the commands already separated by pipes
 * 
 * @param iref reference to the i axis on cmds->tokens
 * at moment of finding an readable pipe character
 * @param cmd_i the command number on wich the create 
 * command is called
 */
void	ft_create_command(t_cmds *cmds, char* str, char* prompt, int n_cmd)
{
	int		i;
    
    i = 0;
    while (str[i] && str[i] == ' ')//por si hay espacios delante
        i++;    
    
    if (str[i] == '"' || str[i] == '\'')//lo que esta entre commilas es comando
    {
        while (str[++i])
            if(str[i] == '"' || str[i] == '\'')
                cmds->binary[n_cmd] = ft_substr(ft_strtrim(cmds->tokens[0], "\""), 0, i);
                
        if(prompt[ft_strlen(cmds->tokens[0])] == ' ')
        {
             cmds->flags[n_cmd] = ft_strjoin(" ", cmds->tokens[1]);
            cmds->command[n_cmd] = ft_strjoin(cmds->binary[0], cmds->flags[0]);
        }       
        else
            if(cmds->tokens[n_cmd + 1])
            {
                cmds->flags[n_cmd] = ft_strdup(cmds->tokens[1]);
             // si esta despues de comillas es flag fijo  
              cmds->command[n_cmd] = ft_strjoin(cmds->binary[n_cmd], cmds->flags[0]);
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
    }}

/**
 * @brief Once every separator or metacharacter has been
clasified, this function creates the definitive version
of the commands separated by pipes
 */
void	ft_parser(t_cmds *cmds, char *prompt, char **arr, int n_comand)
{
	int		i;
    
    i = 0;
    while (arr[0][i] && arr[0][i] == ' ')//por si hay espacios delante
        i++;    
    if (arr[0][i] == '"' || arr[0][i] == '\'')//lo que esta entre commilas es comando
    {
        while (arr[0][++i])
            if(arr[0][i] == '"' || arr[0][i] == '\'')
                cmds->binary[n_comand] = ft_substr(ft_strtrim(arr[0], "\""), 0, i); //elimina comillas
        if(prompt[ft_strlen(arr[0])] == ' ')//si hay espacio al final de comando, coloca espacio
        {
            cmds->flags[n_comand] = ft_strjoin(" ", arr[1]);
            cmds->command[n_comand] = ft_strjoin(cmds->binary[n_comand], cmds->flags[n_comand]);
        }       
        else
            if(arr[1])
            {
            	cmds->flags[n_comand] = ft_strdup(arr[1]);// si esta despues de comillas es flag fijo 
        		cmds->command[n_comand] = ft_strjoin(cmds->binary[n_comand], cmds->flags[n_comand]);
            }
            else
                cmds->command[n_comand] = ft_strdup(cmds->binary[n_comand]);      
    }
    else
    {	
		while(arr[0][i] && arr[0][i] != ' ')
            i++;
        cmds->binary[n_comand] = ft_substr(arr[0], 0, i);  
		if(ft_strlen(arr[0]) - i > 0)
		{
        	cmds->flags[n_comand] = ft_substr(arr[0], i, ft_strlen(arr[0]) - i);
        	cmds->command[n_comand] = ft_strjoin(cmds->binary[n_comand], cmds->flags[n_comand]);
		}
		else
			cmds->command[n_comand]= ft_strdup(cmds->binary[n_comand]);
    }
}

void print_bi_array(char **arr, char *text)
{
	int y;

	y = 0;
	if(!arr && !arr[0][0])
		return;
	while(arr[y] && arr[y][0])
	{
		if(arr[y][0])
			{printf("%d.%s->%s.\n", y, text, arr[y]);
			y++;}
	}
}

void admin_comands(t_cmds *cmds, char* prompt)
{
	int n_tkn;
	int i;
	char **arr;
	int n_comand;
	
	n_tkn = 0;
	n_comand = 0;
	while(cmds->tokens[n_tkn])
	{
		if(cmds->tokens[n_tkn][0] == '|' || !cmds->tokens[n_tkn + 1] )//encuentra pos de pipe
		{
			if(!cmds->tokens[n_tkn + 1])//si es el ultimo
			n_tkn++;
			arr = (char**)malloc(sizeof(char*) * (n_tkn + 1));
			arr[n_tkn] = 0;
			i = -1;
			while(n_tkn > ++i)
				arr[i] = ft_strdup(cmds->tokens[i]);//guarda tokens hasta pipe
			if (cmds->n_cmds > 1)
				ft_parser(cmds, prompt, arr, n_comand);
			else if(cmds->n_cmds == 1)
				ft_parser(cmds, prompt, arr, 0);
			else return ;
			ft_doublefree(arr);
			if(cmds->tokens[0 + n_tkn] )
				cmds->tokens= cmds->tokens + n_tkn;
			else return;
			n_tkn = 0;
			if(cmds->tokens[0][0] == '|')
				cmds->tokens++;
			n_comand++;
			continue;
		}
		n_tkn++;
	}
}

void ft_parsing(t_cmds *cmds, char* prompt)
{
    cmds->binary = (char**)malloc(sizeof(char*) * (cmds->n_cmds + 1));
	cmds->binary[cmds->n_cmds] = 0;
    cmds->flags = (char**)malloc(sizeof(char*) * (cmds->n_cmds + 1));
	cmds->flags[cmds->n_cmds] = 0;
    cmds->command = (char**)malloc(sizeof(char*) * (cmds->n_cmds + 1));
	cmds->command[cmds->n_cmds] = 0;
    
	//mejor enviar copia de token en vez de usar token
	admin_comands(cmds, prompt);
	
	//print_bi_array(cmds->tokens, "tokens");
 	print_bi_array(cmds->binary, "binaries");
    //print_bi_array(cmds->flags, "flags");
	print_bi_array(cmds->command, "comands");
		
}