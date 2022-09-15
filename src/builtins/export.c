#include "../../include/minishell.h"

static void	ft_replace_env(char *variable, t_msh_var *msh, char **tmp)
{
	int		x;
	char	*to_search;

	x = 0;
	while (variable[x] != '=')
			x++;
	to_search = ft_substr(variable, 0, (x + 1));
	msh->own_envp = (char **)malloc(sizeof(char *)
			* (ft_doublestrlen(tmp) + 1));
	x = -1;
	while (tmp[++x])
	{
		if (!ft_strncmp(tmp[x], to_search, ft_strlen(to_search)))
			msh->own_envp[x] = ft_strdup(variable);
		else
		{
			msh->own_envp[x] = ft_strdup(tmp[x]);
		}
	}
	free(to_search);
	msh->own_envp[x] = 0;
}

static void	ft_create_variable(char *variable, t_msh_var *msh)
{
	char	**tmp;
	int		i;

	tmp = ft_doublestrdup(msh->own_envp);
	ft_doublefree(msh->own_envp);
	i = -1;
	if (ft_already_in(variable, tmp))
		ft_replace_env(variable, msh, tmp);
	else
	{
		msh->own_envp = (char **)malloc(sizeof(char *)
				* (ft_doublestrlen(tmp) + 2));
		while (tmp[++i])
			msh->own_envp[i] = ft_strdup(tmp[i]);
		msh->own_envp[i] = ft_strdup(variable);
		msh->own_envp[i + 1] = 0;
	}
	ft_doublefree(tmp);
}

static void	ft_export(char *variable, t_msh_var *msh)
{
	if (ft_check_variable(variable))
		return ;
	ft_create_variable(variable, msh);
}

int	ft_export_check(t_command *command, t_msh_var *msh, int c_num, int count)
{
	int	i;

	if (c_num != count - 1)
		return (1);
	if (command->command[1])
	{
		i = 0;
		while (command->command[++i])
			ft_export(command->command[i], msh);
	}
	else
	{
		i = -1;
		while (msh->own_envp[++i])
			printf("declare -x %s\n", msh->own_envp[i]);
	}
	g_exit_status = 0;
	return (0);
}
