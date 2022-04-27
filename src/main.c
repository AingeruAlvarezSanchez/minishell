/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:06:39 by aalvarez          #+#    #+#             */
/*   Updated: 2022/04/27 14:52:06 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

int	ft_all_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief This is the function that creates all the workflow of the program, 
 * checking initial data, checking separators and metacharacters and sending 
 * the result to the execution functions
 *
 * @param prompt the variable containing the prompt string
 */
void	ft_commands(char *prompt, t_cmds *cmds, t_data *data)
{
	if (!prompt)
		ft_signal_exit(data);
	ft_initials(cmds, data, prompt);
	if (!prompt[0] || ft_all_space(prompt))
	{
		ft_doublefree(cmds->tokens);
		return ;
	}
	if (ft_has_special_char(cmds))
		return ;
	ft_check_metacharacter(cmds, data);
	if (cmds->n_cmds > 1)
		ft_parser(cmds);
	if (cmds->n_cmds == 1)
		ft_mono_command(cmds);
	ft_doublefree(cmds->tokens);
	if (!cmds->commands[0][0])
		return ;
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
		free(cmds.pipefd[0]);
		free(cmds.pipefd[1]);
		free(cmds.pipefd);
	}
	return (0);
}
