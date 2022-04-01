/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:06:39 by aalvarez          #+#    #+#             */
/*   Updated: 2022/04/01 05:01:01 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

/* This function checks wheter there are quotes on the prompt
or not, and stores the result in cmds->tokens for later treatment */
int	ft_quotes_pipes(t_cmds *cmds)
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

/* This is the function that creates all the workflow of the program, checking
initial data, checking separators and metacharacters and sending the result
to the execution functions */
void	ft_commands(char *prompt, t_cmds *cmds, t_data *data)
{
	char	*tmp;
	int i;

	if (!prompt[0])
		return ;
	ft_initials(cmds, data, prompt);
	if (ft_quotes_pipes(cmds))
		return ;
	ft_check_metacharacter(cmds, data);
	cmds->commands = (char **)malloc(sizeof(char *) * (cmds->n_cmds + 1));
	if (cmds->n_cmds > 1)
		ft_parser(cmds);
	else
	{
		i = -1;
		tmp = ft_strdup(" ");
		while (cmds->tokens[++i])
			tmp = ft_strjoin(tmp, cmds->tokens[i]);
		cmds->commands[0] = ft_strdup(ft_strtrim(tmp, " "));
		cmds->commands[1] = 0;
		free(tmp);
	}
	i = -1;
	while (cmds->commands[++i])
		printf("command[%d]: %s\n", i, cmds->commands[i]);
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
