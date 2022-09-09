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

void	ft_trimemptylines(t_cmds *cmds)
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

void	ft_lastjoin(t_cmds *cmds)
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

#include <sys/wait.h>
/**
 * @brief This function checks if the commands are parent or
 * child builtins and sends them to their corresponding handlers
 */
void	    ft_check_builtins(t_cmds *cmds, t_data *data)
{
    int	i;

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

void    ft_commands(t_cmds *cmds, t_data *data)
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

int	main(int argc, char **argv, char **envp)
{
	t_cmds	cmds;
	t_data	data;
	int		status;

    ft_interactive(1);
    ft_signals();
    ft_cpyenv(envp, &data);
    ft_create_pipes(&cmds);
    status = 0;
	while (argc && argv)
	{
		cmds.prompt = readline("ejemplo1 ₺ ");
		add_history(cmds.prompt);
		ft_commands(&cmds, &data);
        waitpid(cmds.pid, NULL, WUNTRACED);
		free(cmds.prompt);
		ft_doublefree(cmds.tokens);
		ft_doublefree(cmds.binary);
		data.g_last_out = WEXITSTATUS(status);
        ft_interactive(1);
	}
	return (0);
}
