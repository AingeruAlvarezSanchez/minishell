#include "../../inc/minishell.h"

char	**ft_unset_env(t_data *Data, __attribute__((unused))char *find, int j)
{
	char	**new;
	int	i;
	int	x;

	i = 0;
	while (Data->env[i])
		i++;
	new = (char **)malloc(sizeof(char *) * i);
	i = -1;
	x = 0;
	while (Data->env[++i])
	{
		if (i == j)
			i++;
		if (!Data->env[i])
			break ;
		new[x++] = ft_strdup(Data->env[i]);
	}
	new[x] = 0;
	ft_doublefree(Data->env);
	return (new);
}

void	ft_unset(__attribute__((unused)) t_data *Data,__attribute__((unused)) t_cmds *Cmds,__attribute__((unused)) int i)
{
	char	*find;
	size_t	len;
	int	j;

	find = Cmds->p_command[i];
	len = ft_strlen(find);
	j = -1;
	while (Data->env[++j])
	{
		if (!ft_strncmp(Data->env[j], find, len))
		{
			Data->env = ft_unset_env(Data, find, j);
			break ;
		}
	}
}

void	ft_check_unset(t_data *Data, t_cmds *Cmds)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	check = 1;
	while (Cmds->p_command[++i])
	{
		j = -1;
		while (Cmds->p_command[i][++j])
		{
			if (Cmds->p_command[i][j] == '=')
			{
				printf("unset: '%s': not a valid identifier\n", Cmds->p_command[i]);
				check = 0;
			}
		}
		if (check == 1)
			ft_unset(Data, Cmds, i);
		check = 1;
	}
}
