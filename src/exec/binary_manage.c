#include "../../include/minishell.h"

bool	gather_bin_path(t_command_table *table, t_msh_var *msh)
{
	int		i;

	i = -1;
	while (++i != table->cmd_count)
	{
		table->commands[i].bin_path = reach_bin_path(&table->commands[i], msh);
		if (!ft_checkparent(&table->commands[i]))
		{
			if (i == table->cmd_count - 1)
				return (ft_isfinal(table, i, table->cmd_count, msh));
			continue ;
		}
		if (table->commands[i].bin_path == NULL)
		{
			if (ft_check_if_is_accesible(table, i))
				continue ;
			printf("%s %s %s", "Minishell :", table->commands[i].command[0],
            ": command not found\n");
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
			if (str_exactly_contains(dirp->d_name, binary_check))
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

char	**get_actual_path(t_msh_var *msh)
{
	char	**path;
	char	*tmp;
	char	**tmp2;
	int		i;

	i = 0;
	while (msh->own_envp && msh->own_envp[++i])
	{
		if (msh->own_envp[i] && str_contains(msh->own_envp[i], "PATH="))
		{
			tmp = ft_strdup(msh->own_envp[i]);
			tmp2 = ft_split(tmp, '=');
			path = ft_split(tmp2[1], ':');
			free(tmp);
			ft_doublefree(tmp2);
			return (path);
		}	
	}
	return (NULL);
}

void	ft_initials_path(t_command *command, t_msh_var *msh)
{
	int	i;	

	i = -1;
	command->path = get_actual_path(msh);
	command->is_absolute = false;
	string_to_lower(command->command[0]);
	i = -1;
	while (command->command[++i])
		ft_trim_algorithm(command, i);
}

//Distribución principal de la ejecución de comandos
char	*reach_bin_path(t_command *command, t_msh_var *msh)
{	
	int		i;
	char	*result;

	ft_initials_path(command, msh);
	i = 0;
	if (command->path)
	{
		while (command->path[i])
		{
			if (return_binary_path(command->path[i], command->command[0]))
				return (ft_get_result(command, i));
			i++;
		}
		if (access(command->command[0], X_OK) == 0)
		{
			result = ft_strdup(command->command[0]);
			command->is_absolute = true;
			return (result);
		}
	}
	if (command->path)
		ft_doublefree(command->path);
	return (NULL);
}
