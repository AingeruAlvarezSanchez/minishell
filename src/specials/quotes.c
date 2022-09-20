#include "../../include/minishell.h"

char	**ft_not_prev(char *tmp, int i, int f, t_cmd *command)
{
	char	**result;

	result = (char **)malloc(sizeof(char *) * 3);
	result[0] = ft_strdup(tmp);
	result[1] = ft_substr(command->cmd[i], (f + 1),
                          ft_strlen(command->cmd[i]) - (f + 1));
	result[2] = 0;
	free(command->cmd[i]);
	if (!result[0][0] && !result[1][0])
		command->cmd[i] = ft_strdup("");
	else
		command->cmd[i] = ft_strjoin(result[0], result[1]);
	return (result);
}

void	ft_quotetrim(t_cmd *command, int i, int final, int j)
{
	char	**str;
	char	*tmp;
	char	*pre;

	pre = ft_substr(command->cmd[i], 0, j);
	tmp = ft_substr(command->cmd[i], (j + 1), (final - (j + 1)));
	if (pre[0])
	{
		str = (char **)malloc(sizeof(char *) * 4);
		str[0] = ft_strdup(pre);
		str[1] = ft_strdup(tmp);
		free(tmp);
		str[2] = ft_substr(command->cmd[i], (final + 1),
                           ft_strlen(command->cmd[i]) - (final + 1));
		str[3] = 0;
		tmp = ft_strjoin(str[0], str[1]);
		free(command->cmd[i]);
		command->cmd[i] = ft_strjoin(tmp, str[2]);
	}
	else
		str = ft_not_prev(tmp, i, final, command);
	ft_doublefree(str);
	free(pre);
	free(tmp);
}

void	ft_trim_algorithm(t_cmd *command, int i)
{
	int		j;
	int		final;

	j = 0;
	while (command->cmd[i][j])
	{
		if (command->cmd[i][j] == '"' || command->cmd[i][j] == '\'')
		{
			final = j + 1;
			while (command->cmd[i][final] && command->cmd[i][final]
                                             != command->cmd[i][j])
				final++;
			ft_quotetrim(command, i, final, j);
			if (final >= ft_strlen(command->cmd[i]))
				return ;
			j = final - 1;
			continue ;
		}
		j++;
	}
}
