/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specials.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:43:04 by ecorreia          #+#    #+#             */
/*   Updated: 2022/09/21 19:43:04 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_has_redir(char *cmd)
{
	if (ft_str_has(cmd, "<<"))
		return (true);
	if (ft_str_has(cmd, ">>"))
		return (true);
	if (ft_str_has(cmd, "<"))
		return (true);
	if (ft_str_has(cmd, ">"))
		return (true);
	return (false);
}

char	*ft_pipe_add(char *prompt)
{
	if (prompt[0] == '|')
	{
		printf("Ejemplo₺: sytax error near unexpected token '|'\n");
		prompt = NULL;
	}
	if (ft_last_nopipe(prompt))
	{
		while (ft_last_nopipe(prompt))
		{
			if (ft_strlen(prompt) > 1)
				prompt = ft_strjoin(prompt, readline("> "));
			else
				prompt = readline("> ");
		}
	}
	return (prompt);
}

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

void	ft_quotetrim(t_cmd *cmd, int i, int final, int j)
{
	char	**str;
	char	*tmp;
	char	*pre;

	pre = ft_substr(cmd->cmd[i], 0, j);
	tmp = ft_substr(cmd->cmd[i], (j + 1), (final - (j + 1)));
	if (pre[0])
	{
		str = (char **)malloc(sizeof(char *) * 4);
		str[0] = ft_strdup(pre);
		str[1] = ft_strdup(tmp);
		free(tmp);
		str[2] = ft_substr(cmd->cmd[i], (final + 1),
			ft_strlen(cmd->cmd[i]) - (final + 1));
		str[3] = 0;
		tmp = ft_strjoin(str[0], str[1]);
		free(cmd->cmd[i]);
		cmd->cmd[i] = ft_strjoin(tmp, str[2]);
	}
	else
		str = ft_not_prev(tmp, i, final, cmd);
	ft_doublefree(str);
	free(pre);
	free(tmp);
}

void	ft_trim_algorithm(t_cmd *cmd, int i)
{
	int		j;
	int		final;

	j = 0;
	while (cmd->cmd[i][j])
	{
		if (cmd->cmd[i][j] == '"' || cmd->cmd[i][j] == '\'')
		{
			final = j + 1;
			while (cmd->cmd[i][final] && cmd->cmd[i][final]
						!= cmd->cmd[i][j])
				final++;
			ft_quotetrim(cmd, i, final, j);
			if (final >= ft_strlen(cmd->cmd[i]))
				return ;
			j = final - 1;
			continue ;
		}
		j++;
	}
}
