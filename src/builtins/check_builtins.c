#include "../../include/minishell.h"

int	ft_isexit(t_cmds_all *table, int c_num, int count)
{
	if (!ft_strncmp(table->cmds[c_num].cmd[0], "exit",
                    (ft_strlen(table->cmds[c_num].cmd[0]) + 1)))
		return (ft_exit(table, c_num, count));
	return (0);
}

int	ft_parent_builtin(t_cmd *command, t_env *msh, int count, int c_num)
{
	if (!ft_strncmp(command->cmd[0], "cd", ft_strlen(command->cmd[0])))
		return (ft_cd(command, msh, count));
	else if (!ft_strncmp(command->cmd[0], "export",
                         (ft_strlen(command->cmd[0]) + 1)))
		return (ft_export_check(command, msh, c_num, count));
	else if (!ft_strncmp(command->cmd[0], "unset",
                         (ft_strlen(command->cmd[0]) + 1)))
		return (ft_check_unset(command, msh, c_num, count));
	return (0);
}

bool	ft_child_builtin(t_cmd *command, t_env *msh)
{
	if (!ft_strncmp(command->cmd[0], "echo",
                    (ft_strlen(command->cmd[0]) + 1)))
	{
		ft_echo(command);
		return (false);
	}
	else if (!ft_strncmp(command->cmd[0], "pwd",
                         (ft_strlen(command->cmd[0]) + 1)))
	{
		ft_pwd();
		return (false);
	}
	else if (!ft_strncmp(command->cmd[0], "env",
                         (ft_strlen(command->cmd[0]) + 1)))
	{
		ft_env(msh, command);
		return (false);
	}
	return (true);
}

int	ft_checkparent(t_cmd *command)
{
	if (!ft_strncmp(command->cmd[0], "cd", ft_strlen(command->cmd[0])))
		return (false);
	else if (!ft_strncmp(command->cmd[0], "export",
                         (ft_strlen(command->cmd[0]) + 1)))
		return (false);
	else if (!ft_strncmp(command->cmd[0], "unset",
                         (ft_strlen(command->cmd[0]) + 1)))
		return (false);
	else if (!ft_strncmp(command->cmd[0], "exit",
                         (ft_strlen(command->cmd[0]) + 1)))
		return (false);
	return (true);
}
