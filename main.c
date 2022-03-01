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

void	ft_setenv(t_data *Data, char **envp)
{
	int	i;
	char	*pwd;

	i = 0;
	pwd = getcwd(NULL, 0);
	while (envp[i])
		i++;
	Data->env = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (ft_strncmp(envp[++i], "OLDPWD=", 7))
	{
		//esta linea da leaks cada vez que se ejecuta un comando, pero no se por que
		Data->env[i] = ft_strdup(envp[i]);
	}
	Data->env[i] = ft_strjoin("OLDPWD=", pwd);
	Data->env[i + 1] = NULL;
	free(pwd);
}	

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv, char **envp)
{
	char	*str;
	t_cmds	Cmds;
	t_data	Data;

	ft_setenv(&Data, envp);
	ft_get_path(&Data);
	while (1)
	{	
		str = readline("ejemplo1 ₺ ");
		add_history(str);
		ft_commands(str, &Cmds, &Data);
		waitpid(Cmds.pid, NULL, WUNTRACED);
		free(str);
	}
	return (0);
}
