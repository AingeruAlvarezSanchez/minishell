#include "../../include/minishell.h"

void	close_and_liberate_execution(t_cmds_all *table)
{
	int	i;

	i = -1;
	close(table->unipipe);
	if (table->n_cmds > 1)
		free(table->pi);
	while (++i < table->n_cmds)
	{
		if (table->cmds[i].absolute && table->cmds[i].path)
			ft_doublefree(table->cmds[i].path);
	}
	ft_free_commands(table);
}

void	ft_struct_free(t_dollars *dollar)
{
	free(dollar->beg);
	free(dollar->final);
	free(dollar->value);
	free(dollar->result);
}

bool	ft_check_if_is_accesible(t_cmds_all *cmds, int pos_cmd)
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
