#include "minishell.h"

void	ft_execute(t_data *Data, char *str)
{
	char * tmp;
	int i = 0;
	
	while (Data->path[i])
	{
		tmp = ft_strjoin(Data->path[i], str);
		if (access(tmp, X_OK) == 0)
			execve(tmp, &str, Data->env);
		free(tmp);
		i++;
	}
	exit(0);
}

void	ft_exec_routine(t_data *Data, t_cmds *Cmds, char *str)
{
	int	i;

	i = -1;
	while (++i < Cmds->n_cmds)
	{
		Cmds->pid = fork();
		if (Cmds->pid == 0)
			ft_execute(Data, str);
	}
}

