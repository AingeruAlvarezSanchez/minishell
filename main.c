/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:10:04 by aalvarez          #+#    #+#             */
/*   Updated: 2022/02/16 21:41:34 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include "libft/libft.h"

/*
https://www.cnblogs.com/hazir/p/instruction_to_readline.html
*/

void	ft_execute(t_data *Data, char * str, char **envp)
{
	char * tmp;
	int i = 0;
	
	while (Data->path[i])
	{
		tmp = ft_strjoin(Data->path[i], str);
		printf("temp = %s\n", tmp);
		if (access(tmp, X_OK) == 0)
		{
			printf("access 0\n");
			int ret = execve(tmp, &str, envp);
			printf("ret = %d\n",ret);
		}
		else
			free(tmp);
		i++;
	}
}

/**
 * @brief get route of path from *envp[]
 * @param Data routes saved in **Data.path with '/' at end of route
 */
void	ft_get_path(t_data *Data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (ft_strncmp(Data->env[i], "PATH=", 5))
		i++;
	Data->env[i] = ft_strtrim(Data->env[i], "PATH=");
	Data->path = ft_split(Data->env[i], ':');
	i = 0;
	while (Data->path[i])
	{
		tmp = ft_strjoin(Data->path[i], "/");
		free(Data->path[i]);
		Data->path[i] = tmp;
		i++;
	}
}

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv, char **envp)
{
	char *str;

	t_data Data;

	Data.env = envp;

	ft_get_path(&Data);

	//int i = 0;
	//while(Data.path[i])
		//printf("%s\n",Data.path[i++]);


	while(1)
	{
		str = readline("ejemoplo1 ₺ ");
			printf("%s\n",str);
		ft_execute( &Data, str, Data.env);
			
		add_history(str);

		free(str);
	}
	
	return(0);
}
