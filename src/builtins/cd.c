/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 07:49:07 by aalvarez          #+#    #+#             */
/*   Updated: 2022/04/07 17:24:12 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>
#include <dirent.h>

char	**ft_oldpwd(t_data *data)
{
	char	**new_env;
	char	*pwd;
	int		i;
	char	*tmp;

	i = 0;
	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin("OLDPWD=", pwd);
	while (data->env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (data->env[++i])
	{
		if (!ft_strncmp(data->env[i], "OLDPWD=", 7))
			new_env[i] = ft_strdup(tmp);
		else
			new_env[i] = ft_strdup(data->env[i]);
	}
	new_env[i] = 0;
	i = -1;
	ft_doublefree(data->env);
	free(pwd);
	free(tmp);
	return (new_env);
}

char	**ft_newpwd(t_data *data)
{
	char	**new_env;
	int		i;
	char	*pwd;
	char	*tmp;

	i = 0;
	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin("PWD=", pwd);
	while (data->env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (data->env[++i])
	{
		if (!ft_strncmp(data->env[i], "PWD=", 4))
			new_env[i] = ft_strdup(tmp);
		else
			new_env[i] = ft_strdup(data->env[i]);
	}
	new_env[i] = 0;
	ft_doublefree(data->env);
	free(tmp);
	free(pwd);
	return (new_env);
}

void	ft_minusflag(t_data *data)
{
	int		i;
	char	*oldpwd;

	i = -1;
	oldpwd = 0;
	while (data->env[++i])
	{
		if (!ft_strncmp(data->env[i], "OLDPWD=", 7))
			oldpwd = ft_strtrim(data->env[i], "OLDPWD=");
	}
	data->env = ft_oldpwd(data);
	printf("%s\n", oldpwd);
	chdir(oldpwd);
	data->last_out = 0;
	data->env = ft_newpwd(data);
	free(oldpwd);
}

void	ft_cd(t_cmds *cmds, t_data *data, int cmd_pos)
{
	if (!cmds->proccess[1])
	{
		data->env = ft_oldpwd(data);
		chdir("/");
		data->last_out = 0;
		data->env = ft_newpwd(data);
	}
	else if (cmds->proccess[1][0] == '-')
		ft_minusflag(data);
	else
	{
		data->env = ft_oldpwd(data);
		if (!opendir(cmds->proccess[1]))
		{
			printf("cd: %s: No such file or directory\n", cmds->proccess[1]);
			data->last_out = 1;
			return ;
		}
		if (cmd_pos != 0)
			return ;
		chdir(cmds->proccess[1]);
		data->last_out = 0;
		data->env = ft_newpwd(data);
	}
}
