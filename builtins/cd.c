/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:45:23 by aalvarez          #+#    #+#             */
/*   Updated: 2022/03/03 12:55:08 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_cd(t_cmds *Cmds, t_data *Data)
{
	int		i;
	char	*old_pwd;

	i = 0;
	ft_oldpwd(Data);
	if (!Cmds->p_command[1])
	{
		chdir("/");
		return ;
	}
	if (!ft_strncmp(Cmds->p_command[1], "-", 1))
	{
		while (ft_strncmp(Data->env[i], "OLDPWD=", 7))
			i++;
		old_pwd = ft_strtrim(Data->env[i], "OLDPWD=");
		printf("OLDPWD: %s\n", old_pwd);
		chdir(old_pwd);
		free(old_pwd);
	}
	else
		chdir(Cmds->p_command[1]);
}
