#include "../../include/minishell.h"

int	ft_isexit(t_command_table *table, int c_num, int count)
{
	if (!ft_strncmp(table->commands[c_num].command[0], "exit",
			(ft_strlen(table->commands[c_num].command[0]) + 1)))
		return (ft_exit(table, c_num, count));
	return (0);
}

int	ft_parent_builtin(t_command *command, t_msh_var *msh, int count, int c_num)
{
	if (!ft_strncmp(command->command[0], "cd", ft_strlen(command->command[0])))
		return (ft_cd(command, msh, count));
	else if (!ft_strncmp(command->command[0], "export",
			(ft_strlen(command->command[0]) + 1)))
		return (ft_export_check(command, msh, c_num, count));
	else if (!ft_strncmp(command->command[0], "unset",
			(ft_strlen(command->command[0]) + 1)))
		return (ft_check_unset(command, msh, c_num, count));
	return (0);
}

bool	ft_child_builtin(t_command *command, t_msh_var *msh)
{
	if (!ft_strncmp(command->command[0], "echo",
			(ft_strlen(command->command[0]) + 1)))
	{
		ft_echo(command);
		return (false);
	}
	else if (!ft_strncmp(command->command[0], "pwd",
			(ft_strlen(command->command[0]) + 1)))
	{
		ft_pwd();
		return (false);
	}
	else if (!ft_strncmp(command->command[0], "env",
			(ft_strlen(command->command[0]) + 1)))
	{
		ft_env(msh, command);
		return (false);
	}
	return (true);
}

int	ft_checkparent(t_command *command)
{
	if (!ft_strncmp(command->command[0], "cd", ft_strlen(command->command[0])))
		return (false);
	else if (!ft_strncmp(command->command[0], "export",
			(ft_strlen(command->command[0]) + 1)))
		return (false);
	else if (!ft_strncmp(command->command[0], "unset",
			(ft_strlen(command->command[0]) + 1)))
		return (false);
	else if (!ft_strncmp(command->command[0], "exit",
			(ft_strlen(command->command[0]) + 1)))
		return (false);
	return (true);
}
