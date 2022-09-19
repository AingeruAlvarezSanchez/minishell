#include "../../include/minishell.h"

bool	ft_isfinal(t_cmds_all *table, int i, int count, t_env *msh)
{
	ft_isexit(table, i, count);
	ft_parent_builtin(&table->cmds[i],
		msh, count, i);
	ft_free_commands(table);
	return (true);
}

char	*ft_get_result(t_cmd *command, int i)
{
	char	*result;

	result = ft_strdup(command->path[i]);
	ft_doublefree(command->path);
	return (result);
}
