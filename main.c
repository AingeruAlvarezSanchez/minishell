/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:10:04 by aalvarez          #+#    #+#             */
/*   Updated: 2022/02/17 17:31:16 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <string.h>
#include "libft/libft.h"

/*
https://www.cnblogs.com/hazir/p/instruction_to_readline.html

TAB keys can be used for command completion
↑ The or  ↓ key can be used to quickly enter historical commands
There are also some interactive line editing shortcuts:
C-A /  C-E move cursor to start/end of line
C-B /  C-F move the cursor one position left/right
C-D delete a character under the cursor
C-K Delete the cursor and all characters from the cursor to the end of the line
C-U Delete all characters from the cursor to the beginning of the line
*/

typedef struct s_data
{
	char **env;
	char **path;
}t_data;

void	ft_execute(t_data *Data, char * str, __attribute__((unused)) char **envp)
{
	char * tmp;
	int i = 0;
	
	while (Data->path[i])
	{
		tmp = ft_strjoin(Data->path[i], str);
		if (access(tmp, X_OK) == 0)
		{
			printf("HELLO\n");
			execve(tmp, &str, envp);////////////////
		}
		else
			free(tmp);
		i++;
	}
}

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv, char **envp)
{
	char *str;
	char **path;
	t_data Data;

	Data.env = envp;

	int	a = 0;	
	int i = 0;
	while(ft_strncmp(envp[i],"PATH=", 5))
		i++;
		
	path = malloc(sizeof(char *) * i);
	path[i] = ft_strtrim(envp[i], "PATH=");
	
	Data.path = ft_split(path[i], ':');

	i = 0;
	while(path[i])
	{
		free(path[i++]);
	}
	
	i = 0;
	while(Data.path[i])
	{
		path[i] = ft_strjoin(Data.path[i], "/");
		free(Data.path[i]);
		Data.path[i] = path[i];
		i++;
	}

	while(1)
	{
		str = readline("ejemoplo1 ₺ ");
		ft_execute( &Data, str, Data.env);

		add_history(str);

		free(str);
	}
	
	return(0);
}
