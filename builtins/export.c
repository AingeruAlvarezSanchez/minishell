#include "../minishell.h"

/*Export deberia funcionar, pero no ha sido probado, es probable que haya algun
overflow, habra que probarlo mas adelante para comprobarlo, el resultado deberia ser
añadir una nueva variable al environment*/
void	ft_export(t_data *Data, char *var_name, char *value)
{
	char 	**tmp;
	int	i;

	i = 0;
	while (Data->env[i]);
		i++;
	tmp = (char **) malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return (NULL);
	i = -1;
	while (Data->env[++i])
		tmp[i] = ft_strdup(Data->env[i]);
	tmp[i] = ft_strjoin(var_name, value);
	i++;
	tmp[i] = NULL;
	free(Data->env);
	Data->env = tmp;
}

