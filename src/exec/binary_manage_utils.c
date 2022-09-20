#include "../../include/minishell.h"

char	*ft_cpy_path(t_cmd *cmd, int pos)
{
	char	*path;

    path = ft_strdup(cmd->path[pos]);
	ft_doublefree(cmd->path);
	return (path);
}

/**
 *
 * @param cmds struct with commands
 * @param pos_cmd actual position of command
 * @param n_cmds number of commands in prompt
 * @param env struct with environment
 * @return 1
 */
bool	ft_final_cmd(t_cmds_all *cmds, int n_cmds, int pos_cmd, t_env *env)
{
    ft_is_exit(cmds, pos_cmd, n_cmds);
	ft_parent_builtin(&cmds->cmds[pos_cmd], env, pos_cmd, pos_cmd);
	ft_free_commands(cmds);
	return (1);
}

