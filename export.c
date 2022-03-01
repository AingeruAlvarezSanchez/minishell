#include "minishell.h"

void	ft_realloc(t_data *Data)
{
	char	**tmp;
	int	i;
	int	j;

	i = 0;
	while (Data->env[i])
		i++;
	j = i;
	tmp = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (Data->env[++i])
		tmp[i] = ft_strdup(Data->env[i]);
	tmp[i] = NULL;
	i = -1;
	while (Data->env[++i])
		free(Data->env[i]);
	free(Data->env);
	Data->env = (char **)malloc(sizeof(char *) * (j + 2));
	i = -1;
	while (tmp[++i])
		Data->env[i] = ft_strdup(tmp[i]);
	Data->env[i] = NULL;
	i = -1;
	while (tmp[++i])
		free(tmp[i]);
	free(tmp);
}

void	ft_export(t_data *Data, t_cmds *Cmds)
{
	int	i;

	i = 0;
	ft_realloc(Data);
	if (!Cmds->p_command[1])
		exit(0);
	while (Data->env[i])
		i++;
	Data->env[i] = ft_strdup(Cmds->p_command[1]); 
	Data->env[i + 1] = NULL;
}
