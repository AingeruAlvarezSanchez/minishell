/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:10:04 by aalvarez          #+#    #+#             */
/*   Updated: 2022/02/17 20:27:25 by aalvarez         ###   ########.fr       */
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

void	ft_initialize_data(t_data *Data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (ft_strncmp(Data->env[i], "PATH=", 5))
		i++;
	Data->path = ft_split(Data->env[i], ':');
	i = -1;
	while (Data->path[++i])
	{
		tmp = ft_strjoin(Data->path[i], "/");
		free(Data->path[i]);
		Data->path[i] = tmp;
	}
	i = 0;
}

void	ft_get_commands(char *str)
{
	int	i;
	int	j;
	t_cmds	Cmds;

	i = 0;
	j = -1;
	Cmds.n_cmds = 0;
	while (str[i])
	{
		printf("HELLO\n");
		if (ft_isalpha(str[i]))
		{
			Cmds.n_cmds += 1;
			while (str[i] != ' ')
				i++;
		}
	}
	printf("Number of commands: %d\n", Cmds.n_cmds);
}

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv, char **envp)
{
	char	*str;
	t_data	Data;

	Data.env = envp;
	ft_initialize_data(&Data);
	while (1)
	{
		str = readline("ejemoplo1 ₺ ");
		add_history(str);
		ft_get_commands(str);
		free(str);
	}
	return (0);
}
