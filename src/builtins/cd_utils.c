#include "../../include/minishell.h"

void	ft_getoldpwd(t_env *msh, char *route)
{
	int		i;
	char	*tmp;

	i = -1;
	msh->oldpwd = getcwd(NULL, 0);
	while (msh->env[++i])
	{
		if (!ft_strncmp(msh->env[i], "OLDPWD=", 7))
		{
			tmp = ft_strjoin("PWD=", route);
			if (ft_strncmp(msh->env[i + 1], tmp, ft_strlen(tmp)))
			{
				free(msh->env[i]);
				msh->env[i] = ft_strjoin("OLDPWD=", msh->oldpwd);
			}
			free(tmp);
			return ;
		}
	}
	ft_firstoldpwd(msh);
}

void	ft_getnewpwd(t_env *msh)
{
	int	i;

	i = -1;
	msh->pwd = getcwd(NULL, 0);
	while (msh->env[++i])
	{
		if (!ft_strncmp(msh->env[i], "PWD=", 4))
		{
			free(msh->env[i]);
			msh->env[i] = ft_strjoin("PWD=", msh->pwd);
		}
	}
}

void	ft_previous_dir(t_env *msh)
{
	int		i;

	i = -1;
	while (msh->env[++i])
	{
		if (!ft_strncmp(msh->env[i], "OLDPWD=", 7))
		{
			msh->oldpwd = ft_substr(msh->env[i + 1], 4,
                                    (ft_strlen(msh->env[i + 1]) - 4));
			free(msh->env[i + 1]);
			msh->pwd = ft_substr(msh->env[i], 7,
                                 (ft_strlen(msh->env[i]) - 7));
			chdir(msh->pwd);
			msh->env[i + 1] = ft_strjoin("PWD=", msh->pwd);
			free(msh->env[i]);
			msh->env[i] = ft_strjoin("OLDPWD=", msh->oldpwd);
			return ;
		}
	}
	printf("Minishell: cd: OLDPWD not set\n");
	msh->oldpwd = NULL;
	msh->pwd = NULL;
}
