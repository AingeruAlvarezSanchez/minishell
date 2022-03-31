/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:06:39 by aalvarez          #+#    #+#             */
/*   Updated: 2022/03/29 16:53:05 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

/* This function checks wheter there are quotes on the prompt
or not, and stores the result in cmds->tokens for later treatment */
int	ft_check_quotes(t_cmds *cmds)
{
	int	i;
	int	j;

	i = -1;
	while (cmds->tokens[++i])
	{
		j = -1;
		while (cmds->tokens[i][++j])
		{
			if (cmds->tokens[i][j] == '\'' || cmds->tokens[i][j] == '"')
			{
				if (cmds->tokens[i][j] == '\'')
					j = ft_quote_error(cmds, i, (j + 1), 0);
				else
					j = ft_quote_error(cmds, i, (j + 1), 1);
				if (j == -1)
					return (1);
				if (cmds->tokens[i][j] == '\'')
					ft_quotes(cmds, i, j, 0);
				else
					ft_quotes(cmds, i, j, 1);
				i++;
				break ;
			}
			else if (cmds->tokens[i][j] == '|' && (cmds->tokens[i][0] != '\''
					&& cmds->tokens[i][0] != '"'))
			{
				if (ft_check_pipes(cmds, i, j))
					return (1);
				cmds->n_cmds++;
				i++;
				break ;
			}
		}
	}
	return (0);
}

/* This function detects if there is a dollar in any
expandible part of the cmds->tokens array and adapts
it to the dollar necessities */
void	ft_check_metacharacter(t_cmds *cmds, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (cmds->tokens[i])
	{
		j = -1;
		while (cmds->tokens[i][++j])
		{
			if (cmds->tokens[i][j] == '$' && cmds->tokens[i][0] != '\'')
			{
				ft_check_dollar(cmds, data, i, j);
				i = -1;
				break ;
			}
		}
		i++;
	}
}

/**
 * @brief 
 * 
 * @param iref This is the reference to the i axis
 * @param cmd_i 
 */
void	ft_create_command(t_cmds *cmds, int iref, int cmd_i)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strdup(" ");
	while (++i < iref)
		tmp = ft_strjoin(tmp, cmds->tokens[i]);
	tmp = ft_strtrim(tmp, " ");
	i = -1;
	while (tmp[++i])
	{
		if (tmp[i] == '|')
		{
			tmp = ft_substr(tmp, (i + 1), ft_strlen(tmp));
			i = -1;
		}
	}
	cmds->commands[cmd_i] = ft_strdup(tmp);
	free(tmp);
	tmp = ft_strdup(" ");
	while (cmds->tokens[++iref])
		tmp = ft_strjoin(tmp, cmds->tokens[iref]);
	tmp = ft_strtrim(tmp, " ");
	cmds->commands[cmd_i + 1] = ft_strdup(tmp);
	free(tmp);
}

/* Once every separator or metacharacter has been
clasified, this function creates the definitive version
of the commands separated by pipes*/
void	ft_parser(t_cmds *cmds)
{
	int	i;
	int	j;
	int	cmd_i;

	cmds->commands = (char **)malloc(sizeof(char *) * (cmds->n_cmds + 1));
	cmd_i = 0;
	i = -1;
	while (cmds->tokens[++i])
	{
		j = -1;
		while (cmds->tokens[i][++j])
		{
			if (cmds->tokens[i][0] == '|')
			{
				ft_create_command(cmds, i, cmd_i);
				cmd_i++;
			}
		}
	}
	if (cmds->n_cmds == 1)
		cmds->commands[cmd_i] = 0;
	else
		cmds->commands[cmd_i + 1] = 0;
	ft_doublefree(cmds->tokens);
}

/* This is the function that creates all the workflow of the program, checking
initial data, checking separators and metacharacters and sending the result
to the execution functions */
void	ft_commands(char *prompt, t_cmds *cmds, t_data *data)
{
	ft_initials(cmds, data, prompt);
	if (ft_check_quotes(cmds))
		return ;
	ft_check_metacharacter(cmds, data);
	int i = -1;
	while (cmds->tokens[++i])
		printf("token[%d]:%s\n", i, cmds->tokens[i]);
	ft_parser(cmds);
	i = -1;
	while (cmds->commands[++i])
		printf("command[%d]:%s\n", i, cmds->commands[i]);
	ft_doublefree(cmds->commands);
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	t_cmds	cmds;
	t_data	data;

	ft_cpyenv(&data, envp);
	ft_get_path(&data);
	while (1 && argc && argv)
	{	
		prompt = readline("ejemplo1 ₺ ");
		add_history(prompt);
		ft_commands(prompt, &cmds, &data);
		waitpid(cmds.pid, NULL, WUNTRACED);
		free(prompt);
	}
	return (0);
}
