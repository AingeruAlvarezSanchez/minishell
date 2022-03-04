/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:10:04 by aalvarez          #+#    #+#             */
/*   Updated: 2022/03/03 18:54:34 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>

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

/* this function creates a copy of the envp variable with malloc */
void	ft_cpyenv(t_data *Data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	Data->env = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		Data->env[i] = ft_strdup(envp[i]);
	Data->env[i] = 0;
}	

void	ft_free_data(t_data *Data)
{
	int	i;

	i = -1;
	while (Data->path[++i])
		free(Data->path[i]);
	free(Data->path);
	i = -1;
	ft_doublefree(Data->path);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_cmds	Cmds;
	t_data	Data;

	ft_cpyenv(&Data, envp);
	ft_get_path(&Data);
	while (1 && argc && argv)
	{	
		str = readline("ejemplo1 ₺ ");
		add_history(str);
		ft_commands(str, &Cmds, &Data);
		waitpid(Cmds.pid, NULL, WUNTRACED);
		free(str);
	}
	return (0);
}
