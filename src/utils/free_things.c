#include "../../include/minishell.h"

bool	ft_check_access(t_cmds_all *cmds, int pos_cmd)
{
	if (access(cmds->cmds[pos_cmd].cmd[0], X_OK) == 0)
	{
        cmds->cmds[pos_cmd].bin_path
			= ft_strdup(cmds->cmds[pos_cmd].cmd[0]);
        cmds->cmds[pos_cmd].absolute = true;
		return (true);
	}
	return (false);
}

void	ft_free_exec(t_cmds_all *cmds)
{
	int	cmd;

    cmd = -1;
	close(cmds->sngl_pipe);
	if (cmds->n_cmds > 1)
		free(cmds->pipes);
	while (++cmd < cmds->n_cmds)
	{
		if (cmds->cmds[cmd].absolute && cmds->cmds[cmd].path)
			ft_doublefree(cmds->cmds[cmd].path);
	}
	ft_free_commands(cmds);
}

/**
 * @brief free dollar struct
 */
void	ft_struct_free(t_dollars *dollar)
{
	free(dollar->beg);
	free(dollar->final);
	free(dollar->value);
	free(dollar->result);
}
