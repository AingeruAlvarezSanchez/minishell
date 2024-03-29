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

static int	ft_check_special(t_cmds_all *cmds, t_env *env)
{
	int	y;
	int	x;

	y = -1;
	while (++y < cmds->n_cmds)
	{
		x = -1;
		while (cmds->cmds[y].cmd[++x])
		{
			if (ft_check_dollars(cmds, y, x, env))
			{
				x = -1;
				continue ;
			}
		}
		if (ft_has_redir(cmds->cmds[y].cmd[x]))
			return (10);
	}
	return (1);
}

static bool	ft_start(char *prompt, t_cmds_all *cmds, t_env *env)
{
	if (ft_check_errors(prompt))
		return (1);
	if (!ft_print_err(ft_parser(prompt, cmds)))
	{
		if (!ft_print_err(ft_check_special(cmds, env)))
		{
			ft_exec(cmds, env);
			return (0);
		}
	}
	return (1);
}

bool	ft_term(t_env *env, t_cmds_all *cmds, char *prompt)
{
	struct termios	termios;
	struct termios	last;

	tcgetattr(STDIN_FILENO, &last);
	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag &= ~(ECHOCTL | ICANON);
	if (ft_strlen(prompt) > 0)
	{
		if (ft_start(prompt, cmds, env))
			return (1);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &last);
	if (prompt != NULL)
		free(prompt);
	return (0);
}

int	main2(t_env *env, char *prompt)
{
	char			*aux;
	t_cmds_all		cmds;

	aux = ft_strtrim(prompt, " ");
	free(prompt);
	add_history(aux);
	if (ft_term(env, &cmds, aux))
	{
		free(aux);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **environ)
{
	char			*prompt;
	t_env			env;

	printf("\nWelcome to Ejemplo\n\n");
	env.env = ft_dup_env(environ);
	env.exp = ft_doublestrdup(env.env);
	g_exit = 0;
	while (1 && argv && argc)
	{
		ft_signals();
		prompt = readline("Ejemplo₺ ");
		if (!prompt)
			ft_sig_exit();
		if (!prompt[0])
		{
			free(prompt);
			continue ;
		}
		if (main2(&env, prompt))
			continue ;
	}
	return (0);
}
