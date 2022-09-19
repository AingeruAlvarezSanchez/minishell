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
		if (table->cmds[i].is_absolute && table->cmds[i].path)
			ft_doublefree(table->cmds[i].path);
	}
	ft_free_commands(table);
}

void	ft_freedollar_struct(t_dollars *dollars)
{
	free(dollars->beg);
	free(dollars->final);
	free(dollars->value);
	free(dollars->result);
}

bool	ft_check_if_is_accesible(t_cmds_all *table, int iterate)
{
	if (access(table->cmds[iterate].cmd[0], X_OK) == 0)
	{
		table->cmds[iterate].bin_path
			= ft_strdup(table->cmds[iterate].cmd[0]);
		table->cmds[iterate].is_absolute = true;
		return (true);
	}
	return (false);
}
