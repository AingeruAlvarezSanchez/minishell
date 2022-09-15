#include "../../include/minishell.h"

static char	*ft_check_value(t_msh_var *msh, char *find, char *tmp)
{
	int	i;

	i = -1;
	while (msh->own_envp[++i])
	{
		if (!ft_strncmp(msh->own_envp[i], find, ft_strlen(find)))
		{
			tmp = ft_substr(msh->own_envp[i], ft_strlen(find),
					(ft_strlen(msh->own_envp[i]) - ft_strlen(find)));
			free(find);
			return (tmp);
		}
	}
	free(find);
	return (NULL);
}

bool	ft_check_char(t_command *com, int a_n, int i, char *refs)
{
	int	x;

	x = -1;
	while (refs[++x])
	{
		if (com->command[a_n][i] == refs[x])
			return (true);
	}
	return (false);
}

char	*ft_dollar_value(t_command *com, t_msh_var *msh, int a_n, int xref)
{
	int		i;
	char	*find;
	char	*tmp;

	i = xref + 1;
	if (ft_check_char(com, a_n, i, " \"\'$?@/:"))
	{
		if (com->command[a_n][i] == '?')
		{
			tmp = ft_itoa(g_exit_status);
			find = ft_strdup(tmp);
			free(tmp);
		}
		else if (com->command[a_n][i] == '$')
			return (NULL);
		else
			find = ft_strdup("$");
		return (find);
	}
	while (com->command[a_n][i] && !ft_check_char(com, a_n, i, " \"\'$?@/:"))
		i++;
	tmp = ft_substr(com->command[a_n], (xref + 1), (i - (xref + 1)));
	find = ft_strjoin(tmp, "=");
	free(tmp);
	return (ft_check_value(msh, find, tmp));
}

int	ft_single_dollar(t_command *com, int a_n, int x)
{
	if (!com->command[a_n][x + 1] && !ft_check_char(com, a_n, x + 1, " \"\'"))
		return (1);
	return (0);
}

void	ft_valuebeg(t_dollars *dollars, t_command *cm, int an, int x)
{
	dollars->result = ft_strjoin(dollars->beg, dollars->value);
	if (x < ft_strlen(cm->command[an])
		|| cm->command[an][x - 1] == '"')
	{
		free(dollars->beg);
		if (cm->command[an][x - 1] == '"')
			dollars->beg = ft_strjoin(dollars->result, "\"");
		else
			dollars->beg = ft_strjoin(dollars->result, dollars->final);
		free(dollars->result);
		dollars->result = ft_strdup(dollars->beg);
	}
}
