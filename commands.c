#include "minishell.h"

void	ft_execute(t_data *Data, char *str)
{
	char * tmp;
	int i = 0;
	
	while (Data->path[i])
	{
		tmp = ft_strjoin(Data->path[i], str);
		if (access(tmp, X_OK) == 0)
			int ret = execve(tmp, &str, Data->env);
		free(tmp);
		i++;
	}
	exit(0);
}
