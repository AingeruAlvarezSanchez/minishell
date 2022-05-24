/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:13:14 by ecorreia          #+#    #+#             */
/*   Updated: 2022/05/24 12:32:04 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <fcntl.h>

void	ft_parser(t_cmds *cmds, char **arr, int cmd_pos)
{
    int     i;
    char    *tmp;

    tmp = ft_deletechar(arr[0], '\"');
    cmds->binary[cmd_pos] = ft_strtrim(tmp, " ");
    free(tmp);
    cmds->command[cmd_pos][0] = ft_strdup(cmds->binary[cmd_pos]);
    i = 0;
    while (arr[++i])
        cmds->command[cmd_pos][i] = ft_deletechar(arr[i],'\"');
}

void ft_until_pipe(t_cmds *cmds, int n_tkn, int n_comand, char ** tkn)
{
    int     i;
    char    **arr;// tokens until pipe
        
    arr = (char**)malloc(sizeof(char*) * (n_tkn + 1));
	arr[n_tkn] = 0;
      i = -1;
	while(n_tkn > ++i)
	    arr[i] = ft_strdup(tkn[i]);//guarda tokens hasta pipe
    arr[i] = 0;
    //print_bi_array(arr, "arr"); //los printeos dan tanto invalid reads (segfaults internos) como leaks
    cmds->command[n_comand] = (char**)malloc(sizeof(char*) * (n_tkn + 1));
    cmds->command[n_comand][n_tkn] = 0;
    ft_parser(cmds, arr, n_comand);
    ft_doublefree(arr);
}

void admin_comands(t_cmds *cmds, char **tkn)
{
	int n_tkn;//token position
	int n_comand; //comand position
    
	n_tkn = 0;
	n_comand = 0;
	while(tkn[n_tkn])
	{
		if(ft_is_pipe_or_redir(tkn[n_tkn][0]) || !tkn[n_tkn + 1])//encuentra pos de pipe
		{	
            if(tkn[n_tkn][0] == '>')/////////////////////tendria que ser cualquier redir pero asi para probar
                cmds->redir_flag = n_comand + 1;
            if (!tkn[n_tkn + 1])
            {
                ft_until_pipe(cmds, n_tkn + 1, n_comand, tkn);
                if(cmds->redir_flag == n_comand)///////////////////////////////////////////////////creo fd del command
                {
                    cmds->redir_fd = open(cmds->command[n_comand][0], O_RDWR | O_CREAT | O_APPEND);
                    if (cmds->redir_fd == -1)
                    {
                        perror("open error");
                        exit(EXIT_FAILURE);
                    }
                }
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
}

void ft_parsing(t_cmds *cmds)
{
    char    **tkn;

    cmds->binary = (char**)malloc(sizeof(char*) * (cmds->n_cmds + 1));
	cmds->binary[cmds->n_cmds] = 0;
    cmds->command = (char***)malloc(sizeof(char**) * (cmds->n_cmds + 1));
	cmds->command[cmds->n_cmds] = 0;
    tkn = ft_doublestrdup(cmds->tokens);
    admin_comands(cmds, tkn);
	
    //los printeos dan tanto invalid reads (segfaults internos) como leaks
	//print_bi_array(cmds->tokens, "tokens");
 	//print_bi_array(cmds->binary, "binaries");
    //int i = 0;
    //while(cmds->command[i])
	//    print_bi_array(cmds->command[i++], "comands");
    ft_doublefree(tkn);
    ft_doublefree(cmds->binary);
}
