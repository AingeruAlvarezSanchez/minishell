/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:07:54 by ecorreia          #+#    #+#             */
/*   Updated: 2022/09/16 21:10:30 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <termios.h>

int	lexer(t_cmds_all *cmds, t_env *msh)
{
	int	i;
	int	x;

	i = -1;
	while (++i < cmds->n_cmds)
	{
		x = 0;
		while (cmds->cmds[i].cmd[x])
		{
			if (ft_check_dollars(cmds, i, x, msh))
			{
				x = 0;
				continue ;
			}
			x++;
		}
		if (ft_has_redir(cmds->cmds[i].cmd[x]))
			return (10);
	}
	return (1);
}

bool	ft_start_program(char *prompt, t_cmds_all *cmds, t_env *env)
{
	if (ft_check_errors(prompt))
		return (1);
	if (!ft_print_err(ft_parser(prompt, cmds)))
	{
		if (!ft_print_err(lexer(cmds, env)))
		{
			execute(cmds, env);
			return (0);
		}
	}
	return (1);
}

bool	ft_readline(t_env *env, t_cmds_all *cmds, char *prompt)
{
	struct termios	termios;
	struct termios	last;

	tcgetattr(STDIN_FILENO, &last);
	tcgetattr(STDIN_FILENO, &termios);
    termios.c_lflag &= ~(ECHOCTL | ICANON);
	if (ft_strlen(prompt) > 0)
	{
		if (ft_start_program(prompt, cmds, env))
			return (1);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &last);
	if (prompt != NULL)
		free(prompt);
	return (0);
}

int	main(int argc, char **argv, char **environ)
{
	char			*aux;
	char			*prompt;
	t_cmds_all	    cmds;
	t_env		    env;

    env.env = ft_dup_env(environ);
    env.exp = ft_doublestrdup(env.env);
	g_exit_status = 0;
	while (1 && argv && argc)
	{
		ft_signals();
        prompt = readline("Ejemplo₺ ");
		if (!prompt)
			ft_signal_exit();
		if (!prompt[0])
		{
			free(prompt);
			continue ;
		}
        aux = ft_strtrim(prompt, " ");
		free(prompt);
		add_history(aux);
		if (ft_readline(&env, &cmds, aux))
		{
			free(aux);
			continue ;
		}
	}
	return (0);
}
