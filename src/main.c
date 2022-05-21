/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 05:41:15 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/21 07:18:02 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

/**
 * @brief If the check_parent function returns true, this function
 * is called in order to check what builtin should be called for 
 * execution
 * 
 * @param cmd_n This is the actual executing command number in
 * all the commands sent by pipes
 */
void	ft_parent_builtin(char** command, t_data *data, int cmd_n)
{    
	if (!ft_strncmp(command[0], "exit", 4)/* && !command[0][4]*/)
		ft_exit(command[1], data, cmd_n);
	else if (!ft_strncmp(command[0], "cd", 2)/* && !command[2]*/)
		ft_cd(command[1], data, cmd_n);
	else if (!ft_strncmp(command[0], "export", 6)/* && !command[6]*/)
		ft_check_export(command, data, cmd_n);
	else if (!ft_strncmp(command[0], "unset", 5)/* && !command[5]*/)
		ft_check_unset(command, data, cmd_n);
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
		if (!ft_check_parent(cmds->command[i][0]))
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
			ft_parent_builtin(cmds->command[i], data, i);
	}
	close(cmds->pipefd[0][READ]);
	close(cmds->pipefd[0][WRITE]);
	close(cmds->pipefd[1][READ]);
	close(cmds->pipefd[1][WRITE]);
	printf("data->last pre: %d\n", data->last_out);
	data->last_out = WEXITSTATUS(status); //data last out no se rellena bien con el WEXITSTATUS 
	printf("data->last post: %d\n", data->last_out);
	ft_triplefree(cmds->command);
}

static void ft_commands(t_cmds *cmds, t_data *data)
{
    char    *tmp;

    ft_initcmds(cmds);
	if (!cmds->prompt)
	{
		free(cmds->prompt);
		ft_signal_exit(data, cmds);	
	}
    tmp = ft_strtrim(cmds->prompt, " ");
    free(cmds->prompt);
    cmds->prompt = ft_strdup(tmp);
    free(tmp);
    if (!cmds->prompt[0])
        return ;
    if (ft_has_special_char(cmds))
    {
		free(cmds->prompt);
        ft_doublefree(cmds->tokens);
        return ;
    }
	free(cmds->prompt);
	ft_dollars(cmds, data);
    ft_parsing(cmds);
    ft_check_builtins(cmds, data);
}

int main(int argc, char **argv, char **envp)
{
    t_cmds  cmds;
    t_data  data;
	
	ft_interactive(1);
	ft_signals();	
    ft_cpyenv(envp, &data);
	ft_create_pipes(&cmds);
    while (1 && argc && argv)
    {
		cmds.prompt = readline("ejemplo1 ₺ ");
		add_history(cmds.prompt);
        ft_commands(&cmds, &data);
        waitpid(cmds.pid, NULL, WUNTRACED);
		ft_interactive(1);
    }
    return (0);
}
