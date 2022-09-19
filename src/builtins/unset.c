#include "../../include/minishell.h"

static bool	ft_not_env(char *variable, t_msh_var *msh)
{
	int	i;

	i = -1;
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], variable, (ft_strlen(variable))))
			return (false);
	}
	return (true);
}

static void	ft_unset(char *variable, t_msh_var *msh)
{
	char	**tmp;
	int		i;
	int		x;

	if (ft_not_env(variable, msh))
		return ;
	else
	{
		tmp = ft_doublestrdup(msh->own_envp);
		ft_doublefree(msh->own_envp);
		msh->own_envp = (char **)malloc(sizeof(char *)
				* (ft_doublestrlen(tmp)));
		i = -1;
		x = -1;
		while (tmp[++i])
		{
			if (ft_strncmp(tmp[i], variable, ft_strlen(variable)))
				msh->own_envp[++x] = ft_strdup(tmp[i]);
		}
		msh->own_envp[x + 1] = 0;
	}
	ft_doublefree(tmp);
}


static bool	ft_not_exp(char *variable, t_msh_var *msh)
{
    int	i;

    i = -1;
    while (msh->exp_envp[++i])
    {
        if (!ft_strncmp(msh->exp_envp[i], variable, (ft_strlen(variable))))
            return (false);
    }
    return (true);
}

static void	ft_unset_exp(char *variable, t_msh_var *msh)
{
    char	**tmp;
    int		i;
    int		x;

    if (ft_not_exp(variable, msh))
        return ;
    else
    {
        tmp = ft_doublestrdup(msh->exp_envp);
        ft_doublefree(msh->exp_envp);
        msh->exp_envp = (char **)malloc(sizeof(char *)
                                        * (ft_doublestrlen(tmp)));
        i = -1;
        x = -1;
        while (tmp[++i])
        {
            if (ft_strncmp(tmp[i], variable, ft_strlen(variable)))
                msh->exp_envp[++x] = ft_strdup(tmp[i]);
        }
        msh->exp_envp[x + 1] = 0;
    }
    ft_doublefree(tmp);
}

bool	ft_check_unset(t_command *command, t_msh_var *msh, int c_num, int count)
{
	int	i;

	if (c_num != count - 1)
		return (1);
	if (command->command[1])
	{
		i = 0;
		while (command->command[++i])
		{
			if (ft_check_variable(command->command[i]))
            {
				ft_unset(command->command[i], msh);
                ft_unset_exp(command->command[i], msh);
            }
		}
	}
	g_exit_status = 0;
	return (0);
}
