/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:22:52 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/23 21:33:06 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <readline/readline.h>

void	interact_signal(int signal)
{
	if (signal == SIGQUIT)
	{
		printf("\33[2K\r");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal == SIGINT)
	{
		write(1,"\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler(int signal)
{
	if (interactive == 1)
	{
		interact_signal(signal);
	}
	else if (interactive == 0)
	{
		if (signal == SIGQUIT)
		{
			interactive = 1;
			write(1,"Quit\n", 5);
			rl_on_new_line();
		}
		if (signal == SIGINT)
		{
			interactive = 1;
			write(1,"\n", 1);
			rl_on_new_line();
		}
	}
}

void ft_signals()
{
    signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

