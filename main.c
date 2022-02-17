/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:10:04 by aalvarez          #+#    #+#             */
/*   Updated: 2022/02/17 17:41:15 by aalvarez         ###   ########.fr       */
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

int	main(int argc, __attribute__((unused)) char **argv, char **envp)
{
	char *str;
	t_data Data;

	Data.env = envp;
	while(1)
	{
		str = readline("ejemoplo1 ₺ ");
		add_history(str);
		pipex(argc, &str, envp);
		free(str);
	}
	
	return(0);
}
