/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:50:53 by ecorreia          #+#    #+#             */
/*   Updated: 2022/09/21 19:50:53 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
Control D out of cat
 */
void	ft_sig_exit(void)
{
	write(1, "exit\n", 5);
	exit(0);
}

/**
 * @param SIGINT  = "control C" inside Cat
 * @param SIGQUIT = "control /" inside cat
 */
void	ft_interactive(int signal)
{
	if (signal == SIGQUIT)
		printf ("Quit: 3\n");
	else if (signal == SIGINT)
		printf ("\n");
}

void	ft_check_sig(void)
{
	signal(SIGINT, ft_interactive);
	signal(SIGQUIT, ft_interactive);
}

/**
 * SIGINT = control C out of cat
 */
void	ft_manage_sig(int signal)
{
	if (rl_on_new_line() == -1)
		exit (-1);
	if (SIGINT == signal)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	ft_signals(void)
{
	signal(SIGINT, ft_manage_sig);
	signal(SIGQUIT, SIG_IGN);
}
