
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param cmds struct with commands
 * @param pos_cmd actual position of command
 * @param n_cmds number of commands in prompt
 */
int ft_is_exit(t_cmds_all *cmds, int pos_cmd, int n_cmds)
{
	if (!ft_strncmp(cmds->cmds[pos_cmd].cmd[0], "exit",
                    (ft_strlen(cmds->cmds[pos_cmd].cmd[0]) + 1)))
		return (ft_exit(cmds, pos_cmd, n_cmds));
	return (0);
}

/**
 * @param cmd struct with command
 * @param env struct with environment
 * @param n_cmds actual position of command
 * @param pos_cmd number of commands in prompt
 * @return 0 if parent
 */
int ft_parent_builtin(t_cmd *cmd, t_env *env, int n_cmds, int pos_cmd)
{
	if (!ft_strncmp(cmd->cmd[0], "cd", ft_strlen(cmd->cmd[0])))
		return (ft_home_cd(cmd, env, n_cmds));
    if (!ft_strncmp(cmd->cmd[0], "export", (ft_strlen(cmd->cmd[0]) + 1)))
		return (ft_export_check(cmd, env, pos_cmd, n_cmds));
    if (!ft_strncmp(cmd->cmd[0], "unset", (ft_strlen(cmd->cmd[0]) + 1)))
		return (ft_check_unset(cmd, env, pos_cmd, n_cmds));
	return (0);
}

/**
 * @param cmd struct with command
 * @param env struct with environment
 * @return 0 if child
 */
bool	ft_child_builtin(t_cmd *cmd, t_env *env)
{
	if (!ft_strncmp(cmd->cmd[0], "echo", (ft_strlen(cmd->cmd[0]) + 1)))
	{
		ft_echo(cmd);
		return (false);
	}
	if (!ft_strncmp(cmd->cmd[0], "pwd", (ft_strlen(cmd->cmd[0]) + 1)))
	{
		ft_pwd();
		return (false);
	}
	if (!ft_strncmp(cmd->cmd[0], "env", (ft_strlen(cmd->cmd[0]) + 1)))
	{
		ft_env(env, cmd);
		return (false);
	}
	return (true);
}

 /**
  * @param cmd struct with command
  * @return 0 if parent
  */
int	ft_checkparent(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->cmd[0], "cd", ft_strlen(cmd->cmd[0])))
		return (false);
	if (!ft_strncmp(cmd->cmd[0], "export", (ft_strlen(cmd->cmd[0]) + 1)))
		return (false);
	if (!ft_strncmp(cmd->cmd[0], "unset", (ft_strlen(cmd->cmd[0]) + 1)))
		return (false);
	if (!ft_strncmp(cmd->cmd[0], "exit", (ft_strlen(cmd->cmd[0]) + 1)))
		return (false);
	return (true);
}
