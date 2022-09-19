#include "../../include/minishell.h"

static bool	ft_not_env(char *variable, t_env *msh)
{
	int	i;

	i = -1;
	while (msh->env[++i])
	{
		if (!ft_strncmp(msh->env[i], variable, (ft_strlen(variable))))
			return (false);
	}
	return (true);
}

static void	ft_unset(char *variable, t_env *msh)
{
	char	**tmp;
	int		i;
	int		x;

	if (ft_not_env(variable, msh))
		return ;
	else
	{
		tmp = ft_doublestrdup(msh->env);
		ft_doublefree(msh->env);
		msh->env = (char **)malloc(sizeof(char *)
                                   * (ft_doublestrlen(tmp)));
		i = -1;
		x = -1;
		while (tmp[++i])
		{
			if (ft_strncmp(tmp[i], variable, ft_strlen(variable)))
				msh->env[++x] = ft_strdup(tmp[i]);
		}
		msh->env[x + 1] = 0;
	}
	ft_doublefree(tmp);
}


static bool	ft_not_exp(char *variable, t_env *msh)
{
    int	i;

    i = -1;
    while (msh->exp[++i])
    {
        if (!ft_strncmp(msh->exp[i], variable, (ft_strlen(variable))))
            return (false);
    }
    return (true);
}

static void	ft_unset_exp(char *variable, t_env *msh)
{
    char	**tmp;
    int		i;
    int		x;

    if (ft_not_exp(variable, msh))
        return ;
    else
    {
        tmp = ft_doublestrdup(msh->exp);
        ft_doublefree(msh->exp);
        msh->exp = (char **)malloc(sizeof(char *)
                                   * (ft_doublestrlen(tmp)));
        i = -1;
        x = -1;
        while (tmp[++i])
        {
            if (ft_strncmp(tmp[i], variable, ft_strlen(variable)))
                msh->exp[++x] = ft_strdup(tmp[i]);
        }
        msh->exp[x + 1] = 0;
    }
    ft_doublefree(tmp);
}

bool	ft_check_unset(t_cmd *command, t_env *msh, int c_num, int count)
{
	int	i;

	if (c_num != count - 1)
		return (1);
	if (command->cmd[1])
	{
		i = 0;
		while (command->cmd[++i])
		{
			if (ft_check_variable(command->cmd[i]))
            {
				ft_unset(command->cmd[i], msh);
                ft_unset_exp(command->cmd[i], msh);
            }
		}
	}
	g_exit_status = 0;
	return (0);
}
