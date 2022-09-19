#include "../../include/minishell.h"

bool	gather_bin_path(t_cmds_all *table, t_env *msh)
{
	int		i;

	i = -1;
	while (++i != table->n_cmds)
	{
		table->cmds[i].bin_path = reach_bin_path(&table->cmds[i], msh);
		if (!ft_checkparent(&table->cmds[i]))
		{
			if (i == table->n_cmds - 1)
				return (ft_isfinal(table, i, table->n_cmds, msh));
			continue ;
		}
		if (table->cmds[i].bin_path == NULL)
		{
			if (ft_check_if_is_accesible(table, i))
				continue ;
			printf("%s %s %s", "Minishell :", table->cmds[i].cmd[0],
            ": cmd not found\n");
			g_exit_status = 127;
			ft_free_commands(table);
			return (true);
		}		
	}
	return (false);
}

bool	return_binary_path(const char *bin_path, char *binary_check)
{
	DIR				*dp;
	struct dirent	*dirp;

	dp = opendir(bin_path);
	if (dp != NULL)
	{
		dirp = readdir(dp);
		while (dirp != NULL)
		{
			if (ft_str_has(dirp->d_name, binary_check))
			{
				closedir(dp);
				return (true);
			}
			dirp = readdir(dp);
		}
		closedir(dp);
	}
	return (false);
}

char	**get_actual_path(t_env *msh)
{
	char	**path;
	char	*tmp;
	char	**tmp2;
	int		i;

	i = 0;
	while (msh->env && msh->env[++i])
	{
		if (msh->env[i] && str_contains(msh->env[i], "PATH="))
		{
			tmp = ft_strdup(msh->env[i]);
			tmp2 = ft_split(tmp, '=');
			path = ft_split(tmp2[1], ':');
			free(tmp);
			ft_doublefree(tmp2);
			return (path);
		}	
	}
	return (NULL);
}

void	ft_initials_path(t_cmd *command, t_env *msh)
{
	int	i;	

	i = -1;
	command->path = get_actual_path(msh);
	command->is_absolute = false;
	string_to_lower(command->cmd[0]);
	i = -1;
	while (command->cmd[++i])
		ft_trim_algorithm(command, i);
}

//Distribución principal de la ejecución de comandos
char	*reach_bin_path(t_cmd *command, t_env *msh)
{	
	int		i;
	char	*result;

	ft_initials_path(command, msh);
	i = 0;
	if (command->path)
	{
		while (command->path[i])
		{
			if (return_binary_path(command->path[i], command->cmd[0]))
				return (ft_get_result(command, i));
            else
                command->path[i] = NULL;
			i++;
		}
		if (access(command->cmd[0], X_OK) == 0)
		{
			result = ft_strdup(command->cmd[0]);
			command->is_absolute = true;
			return (result);
		}
	}
	if (command->path)
		ft_doublefree(command->path);
	return (NULL);
}
