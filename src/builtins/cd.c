/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:36:22 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/03 19:49:28 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_oldpwd(t_data *Data)
{
	int		i;
	char	*old_pwd;

	i = 0;
	old_pwd = getcwd(NULL, 0);
	while (ft_strncmp(Data->env[i], "OLDPWD=", 7))
		i++;
	Data->env[i] = ft_strjoin("OLDPWD=", old_pwd);
	free(old_pwd);
}

void	ft_newpwd(t_data *Data)
{
	int		i;
	char	*pwd;

	i = 0;
	pwd = getcwd(NULL, 0);
	while (ft_strncmp(Data->env[i], "PWD=", 3))
		i++;
	Data->env[i] = ft_strjoin("PWD=", pwd);
	free(pwd);
}

void	ft_cd(t_cmds *Cmds, t_data *Data)
{
	int		i;
	char	*old_pwd;

	i = 0;
	if (!Cmds->p_command[1])
	{
		ft_oldpwd(Data);
		chdir("/");
		ft_newpwd(Data);
	}
	else if (!ft_strncmp(Cmds->p_command[1], "-", 1))
	{
		while (ft_strncmp(Data->env[i], "OLDPWD=", 7))
			i++;
		old_pwd = ft_strtrim(Data->env[i], "OLDPWD=");
		ft_oldpwd(Data);
		chdir(old_pwd);
		ft_newpwd(Data);
		free(old_pwd);
	}
	else
	{
		ft_oldpwd(Data);
		chdir(Cmds->p_command[1]);
		ft_newpwd(Data);
	}
}
