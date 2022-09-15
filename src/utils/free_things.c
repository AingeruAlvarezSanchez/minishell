#include "../../include/minishell.h"

void	close_and_liberate_execution(t_command_table *table)
{
	int	i;

	i = -1;
	close(table->unipipe);
	if (table->cmd_count > 1)
		free(table->pi);
	while (++i < table->cmd_count)
	{
		if (table->commands[i].is_absolute && table->commands[i].path)
			ft_doublefree(table->commands[i].path);
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

bool	ft_check_if_is_accesible(t_command_table *table, int iterate)
{
	if (access(table->commands[iterate].command[0], X_OK) == 0)
	{
		table->commands[iterate].bin_path
			= ft_strdup(table->commands[iterate].command[0]);
		table->commands[iterate].is_absolute = true;
		return (true);
	}
	return (false);
}
