/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:36:22 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/10 16:43:12 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_oldpwd(t_data *Data)
{
	char	**new_env;
	char	*pwd;
	int		i;
	char	*tmp;

	i = 0;
	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin("OLDPWD=", pwd);
	while (Data->env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (Data->env[++i])
	{
		if (!ft_strncmp(Data->env[i], "OLDPWD=", 7))
			new_env[i] = ft_strdup(tmp);
		else
			new_env[i] = ft_strdup(Data->env[i]);
	}
	new_env[i] = 0;
	i = -1;
	ft_doublefree(Data->env);
	free(pwd);
	free(tmp);
	return (new_env);
}

char	**ft_newpwd(t_data *Data)
{
	char	**new_env;
	int		i;
	char	*pwd;
	char	*tmp;

	i = 0;
	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin("PWD=", pwd);
	while (Data->env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (Data->env[++i])
	{
		if (!ft_strncmp(Data->env[i], "PWD=", 4))
			new_env[i] = ft_strdup(tmp);
		else
			new_env[i] = ft_strdup(Data->env[i]);
	}
	new_env[i] = 0;
	ft_doublefree(Data->env);
	free(tmp);
	free(pwd);
	return (new_env);
}

void	ft_minusflag(t_data *Data)
{
	int		i;
	char	*oldpwd;

	i = -1;
	oldpwd = 0;
	while (Data->env[++i])
	{
		if (!ft_strncmp(Data->env[i], "OLDPWD=", 7))
			oldpwd = ft_strtrim(Data->env[i], "OLDPWD=");
	}
	Data->env = ft_oldpwd(Data);
	printf("%s\n", oldpwd);
	chdir(oldpwd);
	Data->env = ft_newpwd(Data);
	free(oldpwd);
}

void	ft_cd(t_cmds *Cmds, t_data *Data)
{
	if (!Cmds->p_command[1])
	{
		Data->env = ft_oldpwd(Data);
		chdir("/");
		Data->env = ft_newpwd(Data);
	}
	else if (Cmds->p_command[1][0] == '-')
		ft_minusflag(Data);
	else
	{
		Data->env = ft_oldpwd(Data);
		chdir(Cmds->p_command[1]);
		Data->env = ft_newpwd(Data);
	}
}
