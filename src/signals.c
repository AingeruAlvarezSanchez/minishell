/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:22:52 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/28 22:47:16 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <readline/readline.h>

//getter - setter
int	ft_interactive(int inter)
{
	static int interactive;

	if(inter == 0 || inter == 1) 
		interactive = inter;
	return interactive;
}

void	ft_signal_exit()
{
	write(1, "exit\n", 5);
	exit(0);
}

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
	if (ft_interactive(-1) == 1)
	{
		interact_signal(signal);
	}
	else if (ft_interactive(-1) == 0)
	{
		if (signal == SIGQUIT)
		{
			ft_interactive(1);
			write(1,"Quit\n", 5);
			rl_on_new_line();
		}
		if (signal == SIGINT)
		{
			ft_interactive(1);
			write(1,"\n", 1);
			rl_on_new_line();
		}
	}
	else printf("%d signal", signal);
}

void ft_signals()
{
    signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

