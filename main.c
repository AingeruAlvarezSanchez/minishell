/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:10:04 by aalvarez          #+#    #+#             */
/*   Updated: 2022/02/20 16:14:51by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv, char **envp)
{
	char	*str;
	t_data	Data;
	t_cmds	Cmds;

	Data.env = envp;
	ft_initialize_data(&Data);
	while (1)
	{
		str = readline("ejemplo1 ₺ ");
		add_history(str);
		ft_commands(str, &Cmds, &Data);
		//ft_exec_routine(&Data, &Cmds, str);
		free(str);
	}
	return (0);
}
