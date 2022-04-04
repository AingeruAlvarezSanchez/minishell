/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:06:39 by aalvarez          #+#    #+#             */
/*   Updated: 2022/04/04 14:15:23 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

/**
 * @brief This function checks wheter there are quotes on the prompt
 * or not, and stores the result in cmds->tokens for later treatment
 */
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

/**
 * @brief This function detects if there is a dollar in any
 * expandible part of the cmds->tokens array and adapts
 * it to the dollar necessities
 */
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

void	ft_init_execute(__attribute__((unused)) t_cmds *cmds,__attribute__((unused)) t_data *data)
{
	printf("Is child builtin\n");
}

/**
 * @brief This function checks if the commands are parent or 
 * child builtins and sends them to their corresponding handlers
 */
void	ft_check_builtins(t_cmds *cmds, t_data *data)
{
	int	i;

	i = -1;
	while (++i < cmds->n_cmds)
	{
		cmds->proccess = ft_split(cmds->commands[i], ' ');
		printf("cmd: %s\n", cmds->proccess[0]);
		if (!ft_check_parent(cmds))
			ft_init_execute(cmds, data);
		else
			ft_parent_builtin(cmds, data, i);
		ft_doublefree(cmds->proccess);
	}
	ft_doublefree(cmds->commands);
}

/**
 * @brief This is the function that creates all the workflow of the program, checking
 * initial data, checking separators and metacharacters and sending the result 
 * to the execution functions
 * 
 * @param prompt the variable containing the prompt string
 */
void	ft_commands(char *prompt, t_cmds *cmds, t_data *data)
{
	if (!prompt)
		ft_signal_exit();
	if (!prompt[0])
		return ;
	ft_initials(cmds, data, prompt);
	if (ft_quotes_pipes(cmds))
		return ;
	ft_check_metacharacter(cmds, data);
	if (cmds->n_cmds > 1)
		ft_parser(cmds);
	else if (cmds->n_cmds == 1)
		ft_mono_command(cmds);
	ft_doublefree(cmds->tokens);
	ft_check_builtins(cmds, data);
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	t_cmds	cmds;
	t_data	data;

	ft_cpyenv(&data, envp);
	ft_get_path(&data);
	ft_interactive(1);
	ft_signals();
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
