/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 22:56:10 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/11 14:01:27 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief If the check_parent function returns true, this function
 * is called in order to check what builtin should be called for 
 * execution
 * 
 * @param cmd_n This is the actual executing command number in
 * all the commands sent by pipes
 */
void	ft_parent_builtin(char *binary, char *flag, t_data *data, int cmd_n)
{
	if (!ft_strncmp(binary, "exit", 4) && !binary[4])
		ft_exit(flag, data, cmd_n);
	else if (!ft_strncmp(binary, "cd", 2) && !binary[2])
		ft_cd(flag, data, cmd_n);
	//else if (!ft_strncmp(binary, "export", 6)
	//	&& !binary[6])
	//	ft_check_export(flag, data, cmd_n);
	//else if (!ft_strncmp(binary, "unset", 5)
	//	&& !binary[5])
	//	ft_check_unset(flag, data, cmd_n);
}

void	ft_execute(t_data *data, const char *command, char *binary, char *flag)
{
	char	*tmp;
	int		i;
	char ** cpy;
	cpy = (char **)malloc(sizeof(char *) * 3);
	
	cpy[0] = ft_strdup(binary);
	if(flag)
		cpy[1] = ft_strdup(flag);
	else
		cpy[1] = 0;
	cpy[2] = 0;
	
	i = -1;
	while (data->paths[++i])
	{
		if (access(binary, X_OK) == 0)
			execve(binary, cpy, data->env);
		tmp = ft_strjoin(data->paths[i], binary);
		if (access(tmp, X_OK) == 0)
			execve(tmp, cpy, data->env);
		free(tmp);
	}
	printf("%s: Command not found\n", command);
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
	//ft_interactive(0);
	if (cmds->pid == 0)
	{
		ft_init_execute(cmds, pos);
		close(cmds->pipefd[0][READ]);
		close(cmds->pipefd[0][WRITE]);
		close(cmds->pipefd[1][READ]);
		close(cmds->pipefd[1][WRITE]);
		ft_execute(data, cmds->command[pos], cmds->binary[pos], cmds->flags[pos]);
	}
}

/**
 * @brief This function checks wheter the builtins created
 * is a parent or a child builtin
 * 
 * @return int If the funcion successes on finding any of the
 * parent builtin names it returns true so the calling function
 * can determine what handler to use
 */
int	ft_check_parent(char *command)
{
	if (!ft_strncmp(command, "exit", 4) && !command[4])
		return (1);
	else if (!ft_strncmp(command, "cd", 2) && !command[2])
		return (1);
	else if (!ft_strncmp(command, "export", 6)
		&& !command[6])
		return (1);
	else if (!ft_strncmp(command, "unset", 5)
		&& !command[5])
		return (1);
	return (0);
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
		if (!ft_check_parent(cmds->command[i]))
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
			ft_parent_builtin(cmds->binary[i], cmds->flags[i], data, i);
		//ft_doublefree(cmds->proccess);
	}
	close(cmds->pipefd[0][READ]);
	close(cmds->pipefd[0][WRITE]);
	close(cmds->pipefd[1][READ]);
	close(cmds->pipefd[1][WRITE]);
	data->last_out = WEXITSTATUS(status);
	//ft_doublefree(cmds->commands);
}

static void ft_commands(char *prompt, t_data *data, t_cmds *cmds/*, t_proc *proc*/)
{	
    if (!prompt[0])
        return ;
    ft_initcmds(prompt, cmds);
    if (ft_has_special_char(cmds))
    {
        ft_doublefree(cmds->tokens);
		return ;
    }
    ft_check_metacharacter(cmds, data);

    ft_parsing(cmds, prompt);

    ft_doublefree(cmds->tokens);
    //if (!cmds->command[0][0])
	//	return ;
	ft_check_builtins(cmds, data);
}

int main(int argc, char **argv, char **envp)
{
    char		*prompt;
	t_cmds		cmds;
	t_data		data;
	//t_proc      proc;

	ft_cpyenv(&data, envp);
	/*ft_interactive(1);
	ft_signals();*/
	while (1 && argc && argv)
	{
		prompt = readline("ejemplo1 ₺ ");
		add_history(prompt);
		ft_commands(prompt, &data, &cmds/*, &proc*/);
		waitpid(cmds.pid, NULL, WUNTRACED);
        free(prompt);	
	}
	return (0);
    
}