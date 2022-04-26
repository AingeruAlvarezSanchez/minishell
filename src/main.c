/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:06:39 by aalvarez          #+#    #+#             */
/*   Updated: 2022/04/26 19:01:55 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

int	ft_is_special_char(char c)
{
	if (c == '\'' || c == '"' || c == '<' || c == '>'
		|| (c == '|' && (c != '\'' && c != '"')))
		return (1);
	return (0);
}

int	ft_manage_special_char(int y, int x, t_cmds *cmds)
{
	if (cmds->tokens[y][x] == '\'' || cmds->tokens[y][x] == '"')
	{
		x = ft_quote_error(cmds, y, (x + 1), cmds->tokens[y][x]);
		if (x == -1)
			return (1);
		ft_quotes(cmds, y, x, cmds->tokens[y][x]);
	}
	else if (cmds->tokens[y][x] == '|' && (cmds->tokens[y][0] != '\''
		&& cmds->tokens[y][0] != '"'))
	{
		if (ft_check_pipes(cmds, y, x))
			return (1);
		cmds->n_cmds++;
	}
	else if (cmds->tokens[y][x] == '>')
	{
		printf("redirections");
		return (1);
	}
	return (0);
}

int	ft_has_special_char(t_cmds *cmds)
{
	int	y;
	int	x;

	y = -1;
	while (cmds->tokens[++y])
	{
		x = -1;
		while (cmds->tokens[y][++x])
		{
			if (ft_is_special_char(cmds->tokens[y][x]))
			{
				if (ft_manage_special_char(y, x, cmds))
					return (1);
				y++;
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
	int	y;
	int	x;

	y = 0;
	while (cmds->tokens[y])
	{
		x = -1;
		while (cmds->tokens[y][++x])
		{
			if (cmds->tokens[y][x] == '$' && cmds->tokens[y][0] != '\'')
			{
				ft_check_dollar(cmds, data, y, x);
				y = -1;
				break ;
			}
		}
		y++;
	}
}

void	ft_execute(t_data *data, t_cmds *cmds)
{
	char	*tmp;
	int		i;

	i = -1;
	while (data->path[++i])
	{
		if (access(cmds->proccess[0], X_OK) == 0)
			execve(cmds->proccess[0], cmds->proccess, data->env);
		tmp = ft_strjoin(data->path[i], cmds->proccess[0]);
		if (access(tmp, X_OK) == 0)
			execve(tmp, cmds->proccess, data->env);
		free(tmp);
	}
	printf("%s: Command not found\n", cmds->proccess[0]);
	exit(0);
}

void	ft_init_execute(t_cmds *cmds, int pos)
{
	if (cmds->n_cmds != 1)
	{
		if (pos == 0)
		{
			if (cmds->n_cmds > 2)
				dup2(cmds->pipefd[1][WRITE], STDOUT_FILENO);
			else
				dup2(cmds->pipefd[0][WRITE], STDOUT_FILENO);
		}
		else if (pos != 0 && pos != cmds->n_cmds - 1)
		{
			dup2(cmds->pipefd[1][WRITE], STDOUT_FILENO);
			dup2(cmds->pipefd[0][READ], STDIN_FILENO);
		}
		else if (pos == cmds->n_cmds - 1)
			dup2(cmds->pipefd[0][READ], STDIN_FILENO);
	}
}

/**
 * @brief This function creates all the necesary forks
 * in order to execute every command
 * 
 * @param pos command number
 */
void	ft_create_forks(t_cmds *cmds, t_data *data, int pos)
{
	cmds->pid = fork();
	ft_interactive(0);
	if (cmds->pid == 0)
	{
		ft_init_execute(cmds, pos);
		close(cmds->pipefd[0][READ]);
		close(cmds->pipefd[0][WRITE]);
		close(cmds->pipefd[1][READ]);
		close(cmds->pipefd[1][WRITE]);
		ft_execute(data, cmds);
	}
}

/**
 * @brief This function checks if the commands are parent or
 * child builtins and sends them to their corresponding handlers
 */
void	ft_check_builtins(t_cmds *cmds, t_data *data)
{
	int	i;
	int	status;

	status = 0;
	pipe(cmds->pipefd[0]);
	pipe(cmds->pipefd[1]);
	i = -1;
	while (++i < cmds->n_cmds)
	{
		if(ft_strchr(cmds->commands[i], '"'))
		{
			cmds->proccess = ft_split(cmds->commands[i], '"');
			if(cmds->proccess[1])
				cmds->proccess[0] = ft_strtrim(cmds->proccess[0], " ");
		}
		else
			cmds->proccess = ft_split(cmds->commands[i], ' ');
		if (!ft_check_parent(cmds))
		{
			ft_create_forks(cmds, data, i);
			if (cmds->n_cmds > 2)
			{
				close(cmds->pipefd[0][0]);
				close(cmds->pipefd[0][1]);
				waitpid(cmds->pid, &status, 0);
				cmds->pipefd[0][0] = cmds->pipefd[1][0];
				cmds->pipefd[0][1] = cmds->pipefd[1][1];
				pipe(cmds->pipefd[1]);
			}
		}
		else
			ft_parent_builtin(cmds, data, i);
		ft_doublefree(cmds->proccess);
	}
	close(cmds->pipefd[0][READ]);
	close(cmds->pipefd[0][WRITE]);
	close(cmds->pipefd[1][READ]);
	close(cmds->pipefd[1][WRITE]);
	data->last_out = WEXITSTATUS(status);
	ft_doublefree(cmds->commands);
}


int ft_all_space(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if(str[i] != ' ')
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
