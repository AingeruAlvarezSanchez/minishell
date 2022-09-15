#include "../../include/minishell.h"

void	ft_getoldpwd(t_msh_var *msh, char *route)
{
	int		i;
	char	*tmp;

	i = -1;
	msh->oldpwd = getcwd(NULL, 0);
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], "OLDPWD=", 7))
		{
			tmp = ft_strjoin("PWD=", route);
			if (ft_strncmp(msh->own_envp[i + 1], tmp, ft_strlen(tmp)))
			{
				free(msh->own_envp[i]);
				msh->own_envp[i] = ft_strjoin("OLDPWD=", msh->oldpwd);
			}
			free(tmp);
			return ;
		}
	}
	ft_firstoldpwd(msh);
}

void	ft_getnewpwd(t_msh_var *msh)
{
	int	i;

	i = -1;
	msh->pwd = getcwd(NULL, 0);
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], "PWD=", 4))
		{
			free(msh->own_envp[i]);
			msh->own_envp[i] = ft_strjoin("PWD=", msh->pwd);
		}
	}
}

void	ft_previous_dir(t_msh_var *msh)
{
	int		i;

	i = -1;
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], "OLDPWD=", 7))
		{
			msh->oldpwd = ft_substr(msh->own_envp[i + 1], 4,
					(ft_strlen(msh->own_envp[i + 1]) - 4));
			free(msh->own_envp[i + 1]);
			msh->pwd = ft_substr(msh->own_envp[i], 7,
					(ft_strlen(msh->own_envp[i]) - 7));
			chdir(msh->pwd);
			msh->own_envp[i + 1] = ft_strjoin("PWD=", msh->pwd);
			free(msh->own_envp[i]);
			msh->own_envp[i] = ft_strjoin("OLDPWD=", msh->oldpwd);
			return ;
		}
	}
	printf("Minishell: cd: OLDPWD not set\n");
	msh->oldpwd = NULL;
	msh->pwd = NULL;
}
