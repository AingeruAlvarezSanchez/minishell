#include "../../include/minishell.h"

char	**ft_not_prev(char *tmp, int i, int f, t_command *command)
{
	char	**result;

	result = (char **)malloc(sizeof(char *) * 3);
	result[0] = ft_strdup(tmp);
	result[1] = ft_substr(command->command[i], (f + 1),
			ft_strlen(command->command[i]) - (f + 1));
	result[2] = 0;
	free(command->command[i]);
	if (!result[0][0] && !result[1][0])
		command->command[i] = ft_strdup("");
	else
		command->command[i] = ft_strjoin(result[0], result[1]);
	return (result);
}

void	ft_quotetrim(t_command *command, int i, int final, int j)
{
	char	**str;
	char	*tmp;
	char	*pre;

	pre = ft_substr(command->command[i], 0, j);
	tmp = ft_substr(command->command[i], (j + 1), (final - (j + 1)));
	if (pre[0])
	{
		str = (char **)malloc(sizeof(char *) * 4);
		str[0] = ft_strdup(pre);
		str[1] = ft_strdup(tmp);
		free(tmp);
		str[2] = ft_substr(command->command[i], (final + 1),
				ft_strlen(command->command[i]) - (final + 1));
		str[3] = 0;
		tmp = ft_strjoin(str[0], str[1]);
		free(command->command[i]);
		command->command[i] = ft_strjoin(tmp, str[2]);
	}
	else
		str = ft_not_prev(tmp, i, final, command);
	ft_doublefree(str);
	free(pre);
	free(tmp);
}

void	ft_trim_algorithm(t_command *command, int i)
{
	int		j;
	int		final;

	j = 0;
	while (command->command[i][j])
	{
		if (command->command[i][j] == '"' || command->command[i][j] == '\'')
		{
			final = j + 1;
			while (command->command[i][final] && command->command[i][final]
					!= command->command[i][j])
				final++;
			ft_quotetrim(command, i, final, j);
			if (final >= ft_strlen(command->command[i]))
				return ;
			j = final - 1;
			continue ;
		}
		j++;
	}
}
