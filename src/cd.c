#include "../inc/minishell.h"

void	ft_set_env(t_data *Data)
{
	int	i;
	char	*route;

	i = 0;
	route = getcwd(NULL, 0);
	while (ft_strncmp(Data->env[i], "OLDPWD=", 7))
		i++;
	//la linea de codigo de justo debajo da leaks a partir del segundo uso de un comando
	Data->env[i] = ft_strjoin("OLDPWD=", route);
	free(route);
}

void	ft_cd(t_cmds *Cmds, t_data *Data)
{
	ft_set_env(Data);
	if (!Cmds->p_command[1])
	{
		chdir("/");
		return ;
	}
	/*if (!ft_strncmp(Cmds->p_command[1], "-", 1))
		chdir(old_route);*/
	//else
		chdir(Cmds->p_command[1]);
}

