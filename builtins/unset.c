#include "../minihell.h"

/*Esta funcion no ha sido probada, puede dar algun error de overflow
esta pendiente de ser probada, el resultado deberia ser que se borre var_name
de la variable environment*/
void	ft_unset(t_data *Data, char *var_name)
{
	char 	**tmp;
	int	i;

	i = 0;
	while (Data->env[i])
		i++;
	tmp = (char **) malloc(sizeof(char *) * (i));
	if (!tmp)
		return ;
	i = -1;
	while (Data->env[++i])
	{
		if (ft_strncmp(Data->env[i], var_name))
			i++;
		tmp = ft_strdup(Data->env[i]);
	}
	tmp[i] = NULL;
	Data->env = tmp;
}

