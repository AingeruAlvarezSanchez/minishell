/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 04:27:25 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/06 19:40:33 by ecorreia         ###   ########.fr       */
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
void	ft_parser(t_cmds *cmds, char *prompt)
{
	int	y;
	int	x;
	int	cmd_pos;

	cmd_pos = 0;
	y = 0;
	while (cmds->tokens[y])
	{
		x = 0;
		while (cmds->tokens[y][x])
		{
			if (cmds->tokens[y][0] == '|' && cmds->tokens[y -1])
				ft_create_command(cmds, cmds->tokens[y + 1], prompt, cmd_pos++);
			x++;
		}
		y++;
	}
	if (cmds->n_cmds > 2)
	{
		y = -1;
		while (cmds->command[++y])
		{
			x = -1;
			while (cmds->command[y][++x])
			{
				if (cmds->command[y][x] == '|')
				{
					//ft_revsubstr(cmds, y, '|');
					break ;
				}
			}
		}
	}
}

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
		if(ft_strlen(cmds->tokens[0]) - i)
		{
        	cmds->flags[0] = ft_substr(cmds->tokens[0], i, ft_strlen(cmds->tokens[0]) - i);
        	cmds->command[0] = ft_strjoin(cmds->binary[0], cmds->flags[0]);
		}
		else
			cmds->command[0]= ft_strdup(cmds->binary[0]);
    }

	cmds->binary[1] = 0;
	cmds->flags[1] = 0;
	cmds->command[1] = 0;
}


void print_bi_array(char **arr, char *text)
{
	int y;

	y = 0;

	if(!arr)
		return;
	
	while(arr[y])
	{
		printf("%d.%s->%s.\n", y, text, arr[y]);
		y++;
	}
}

void ft_parsing(t_cmds *cmds, char* prompt)
{
    cmds->binary = (char**)malloc(sizeof(char*) * 2);
    cmds->flags = (char**)malloc(sizeof(char*) * 2);
    cmds->command = (char**)malloc(sizeof(char*) * 2);

    if (cmds->n_cmds > 1)
		ft_parser(cmds, prompt);
    else if(cmds->n_cmds == 1)
    	ft_mono_command(cmds, prompt);
    else return ;
	print_bi_array(cmds->tokens, "tokens");
 	print_bi_array(cmds->binary, "binaries");
    print_bi_array(cmds->flags, "flags");
	print_bi_array(cmds->command, "comands");
		
}