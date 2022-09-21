/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_val.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:46:32 by ecorreia          #+#    #+#             */
/*   Updated: 2022/09/21 19:46:32 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param env struct with environment
 * @param var variable to check
 * @return NULL if no var
 */
static char	*ft_check_var(t_env *env, char *var)
{
	char	*tmp;
	int		i;

	i = -1;
	while (env->env[++i])
	{
		if (!ft_strncmp(env->env[i], var, ft_strlen(var)))
		{
			tmp = ft_substr(env->env[i],
					ft_strlen(var), (ft_strlen(env->env[i]) - ft_strlen(var)));
			free(var);
			return (tmp);
		}
	}
	free(var);
	return (NULL);
}

/**
 * @param cmd struct with command
 * @param x command argument position
 * @param c char to check
 * @param specials specials chars to check
 * @return 1 if special char inside
 */
bool	ft_check_char(t_cmd *cmd, int x, int c, char *specials)
{
	int	i;

	i = -1;
	while (specials[++i])
	{
		if (cmd->cmd[x][c] == specials[i])
			return (1);
	}
	return (0);
}

char	*ft_dollar_value(t_cmd *cmd, t_env *env, int x, int xref)
{
	int		c;
	char	*var;
	char	*aux;

	c = xref + 1;
	if (ft_check_char(cmd, x, c, " \"\'$?@/:"))
	{
		if (cmd->cmd[x][c] == '?')
		{
			aux = ft_itoa(g_exit);
			var = ft_strdup(aux);
			free(aux);
		}
		else if (cmd->cmd[x][c] == '$')
			return (NULL);
		else
			var = ft_strdup("$");
		return (var);
	}
	while (cmd->cmd[x][c] && !ft_check_char(cmd, x, c, " \"\'$?@/:"))
		c++;
	aux = ft_substr(cmd->cmd[x], (xref + 1), (c - (xref + 1)));
	var = ft_strjoin(aux, "=");
	free(aux);
	return (ft_check_var(env, var));
}

/**
 * @param cmd struct with command
 * @param x variable position
 * @param c char to check
 * @return
 */
int	ft_single_dollar(t_cmd *cmd, int x, int c)
{
	if (!cmd->cmd[x][c + 1])
		return (0);
	if (!ft_check_char(cmd, x, c + 1, " \"\'"))
		return (1);
	return (0);
}

/**
 * @param dollar struct with dollar data
 * @param cmd struct with command
 * @param x variable position
 * @param xref reference position
 */
void	ft_valuebeg(t_dollar *dollar, t_cmd *cmd, int x, int xref)
{
	dollar->result = ft_strjoin(dollar->pre, dollar->val);
	if (xref < ft_strlen(cmd->cmd[x]) || cmd->cmd[x][xref - 1] == '"')
	{
		free(dollar->pre);
		if (cmd->cmd[x][xref - 1] == '"')
			dollar->pre = ft_strjoin(dollar->result, "\"");
		else
			dollar->pre = ft_strjoin(dollar->result, dollar->final);
		free(dollar->result);
		dollar->result = ft_strdup(dollar->pre);
	}
}
