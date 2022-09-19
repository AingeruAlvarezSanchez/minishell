#include "../../include/minishell.h"

char	*ft_get_home(t_env *msh)
{
	int	i;

	i = -1;
	while (msh->env[++i])
	{
		if (!ft_strncmp(msh->env[i], "HOME=", 5))
			return (ft_substr(msh->env[i], 5,
                              ft_strlen(msh->env[i]) - 5));
	}
	printf("HOME not set\n");
	return (NULL);
}

void	ft_firstoldpwd(t_env *msh)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	j = 0;
	tmp = ft_doublestrdup(msh->env);
	ft_doublefree(msh->env);
	msh->env = (char **)malloc(sizeof(char *)
                               * (ft_doublestrlen(tmp) + 2));
	while (tmp[++i])
	{
		if (!ft_strncmp(tmp[i], "PWD=", 4))
		{
			msh->env[j] = ft_strjoin("OLDPWD=", msh->oldpwd);
			j++;
		}
		msh->env[j++] = ft_strdup(tmp[i]);
	}
	msh->env[j] = 0;
	ft_doublefree(tmp);
}

bool	cd_extension(t_cmd *command, t_env *msh)
{
	ft_getoldpwd(msh, command->cmd[1]);
	if (chdir(command->cmd[1]) == -1)
	{
		printf("cd: %s: No such file or directory\n", command->cmd[1]);
		g_exit_status = 1;
		free(msh->oldpwd);
		return (true);
	}
	ft_getnewpwd(msh);
	return (false);
}

bool	ft_cd(t_cmd *command, t_env *msh, int count)
{
	char	*home;

	if (count != 1)
		return (true);
	if (!command->cmd[1] || command->cmd[1][0] == '~')
	{
		home = ft_get_home(msh);
		ft_getoldpwd(msh, home);
		chdir(home);
		ft_getnewpwd(msh);
		free(home);
	}
	else if (command->cmd[1][0] == '-')
		ft_previous_dir(msh);
	else
	{
		if (cd_extension(command, msh))
			return (false);
	}
	free(msh->oldpwd);
	free(msh->pwd);
	g_exit_status = 0;
	return (false);
}
