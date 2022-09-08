/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 05:41:15 by aalvarez          #+#    #+#             */
/*   Updated: 2022/09/05 00:48:36 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	ft_trimemptylines(t_cmds *cmds)
{
	int		i;
	int		j;
	int		size;
	char	**tmp;

	i = -1;
	size = 0;
	while (cmds->tokens[++i])
	{
		if (cmds->tokens[i][0])
			size++;
	}
	tmp = ft_doublestrdup(cmds->tokens);
	ft_doublefree(cmds->tokens);
	i = -1;
	j = -1;
	cmds->tokens = (char **)malloc(sizeof(char *) * (size + 1));
	while (tmp[++i])
	{
		if (tmp[i][0])
			cmds->tokens[++j] = ft_strdup(tmp[i]);
	}
	cmds->tokens[j + 1] = 0;
	ft_doublefree(tmp);
}

static void	ft_lastjoin(t_cmds *cmds)
{
	char	**tmp;
	int		i;

	tmp = ft_doublestrdup(cmds->tokens);
	ft_doublefree(cmds->tokens);
	if (!tmp)
	{
		cmds->tokens = (char **)malloc(sizeof(char *) * 2);
		cmds->tokens[0] = ft_strdup(cmds->prompt);
		cmds->tokens[1] = 0;
	}
	else
	{
		i = -1;
		cmds->tokens = (char **)malloc(sizeof(char *)
				* (ft_doublestrlen(tmp) + 2));
		while (tmp[++i])
			cmds->tokens[i] = ft_strdup(tmp[i]);
		cmds->tokens[i] = ft_strdup(cmds->prompt);
		cmds->tokens[i + 1] = 0;
	}
	ft_trimemptylines(cmds);
	ft_doublefree(tmp);
}

////////////////////////////


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

void	ft_child_builtin(char **command, t_data *Data)
{
    if (!ft_strncmp(command[0], "pwd", 3))
        ft_pwd();
    else if (!ft_strncmp(command[0], "echo", 4))
        ft_check_echo(command);
    else if (!ft_strncmp(command[0], "env", 3))
        ft_env(Data);
}

void	ft_execute(t_data *data, char **command, t_cmds *cmds)
{
    char	*tmp;
    int		i;

    i = -1;
    //updatePath(data); //TODO: need to update path before using it
    ft_child_builtin(cmds->command[0], data); //TODO:
    while (data->paths[++i])
    {
        if (access(command[0], X_OK) == 0)
            execve(command[0], command, data->env);
        tmp = ft_strjoin(data->paths[i], command[0]);
        if (access(tmp, X_OK) == 0)
            execve(tmp, command, data->env);
        free(tmp);
    }
    printf("%s: Command not found\n", command[0]);

    exit(0);
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
        ft_execute(data, cmds->command[pos], cmds);
    }
}
/**
 * @brief If the check_parent function returns true, this function
 * is called in order to check what builtin should be called for
 * execution
 *
 * @param cmd_n This is the actual executing command number in
 * all the commands sent by pipes
 */
void	ft_parent_builtin(char** command, t_data *data, int cmd_n, t_cmds *cmds)
{
    if (!ft_strncmp(command[0], "exit", 4)/* && !command[0][4]*/)
        ft_exit(command[1], data, cmd_n, cmds);
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
#include <sys/wait.h>
/**
 * @brief This function checks if the commands are parent or
 * child builtins and sends them to their corresponding handlers
 */
void	    ft_check_builtins(t_cmds *cmds, t_data *data) //TODO: mover
{
    int	i;
    //int	status;

   // status = 0;
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
                //waitpid(cmds->pid, &status, 0);//TODO: wait here?
                cmds->pipefd[0][0] = cmds->pipefd[1][0];
                cmds->pipefd[0][1] = cmds->pipefd[1][1];
                pipe(cmds->pipefd[1]);
            }
        }
        else
            ft_parent_builtin(cmds->command[i], data, i, cmds);
    }
    close(cmds->pipefd[0][READ]);
    close(cmds->pipefd[0][WRITE]);
    close(cmds->pipefd[1][READ]);
    close(cmds->pipefd[1][WRITE]);
    ft_triplefree(cmds->command);
}

static void	    ft_commands(t_cmds *cmds, t_data *data)
{
	char	*tmp;

	ft_initcmds(cmds);
	if (!cmds->prompt)
		ft_signal_exit(data, cmds); //TODO:free(cmds->prompt);
	tmp = ft_strtrim(cmds->prompt, " ");
	free(cmds->prompt);
	cmds->prompt = ft_strdup(tmp);
	free(tmp);
	if (!cmds->prompt[0])
		return ;
	if (ft_has_special_char(cmds))
		return ;
	if (cmds->prompt[0])
		ft_lastjoin(cmds);
	if (!cmds->tokens)
		return ;
	ft_dollars(cmds, data);
	ft_parsing(cmds, data);
    ft_check_builtins(cmds, data);
}

void	ft_create_pipes(t_cmds *cmds) // TODO: mover a otro sitio
{
    cmds->pipefd = (int **)malloc(sizeof(int *) * 2);
    cmds->pipefd[0] = (int *)malloc(sizeof(int) * 2);
    cmds->pipefd[1] = (int *)malloc(sizeof(int) * 2);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmds	cmds;
	t_data	data;
	int		status;

    ft_interactive(1);
    ft_signals();
    ft_cpyenv(envp, &data);
    ft_create_pipes(&cmds);
	while (argc && argv)
	{
		cmds.prompt = readline("ejemplo1 ₺ ");
		add_history(cmds.prompt);
		ft_commands(&cmds, &data);
        waitpid(cmds.pid, &status, WUNTRACED);
		free(cmds.prompt);
		ft_doublefree(cmds.tokens);
		ft_doublefree(cmds.binary);
		data.g_last_out = WEXITSTATUS(status);
        ft_interactive(1);
	}
	return (0);
}
