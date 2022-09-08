/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:40:09 by aalvarez          #+#    #+#             */
/*   Updated: 2022/09/04 21:57:33 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <readline/readline.h>

/**
 * @brief get or set the value of the variable interactive
 *
 * @param inter if 0 or 1 changes the value. if -1 just get the value.
 * @return the value of interactive
 */
int	ft_interactive(int inter)
{
    static int	interactive;

    if (inter == 0 || inter == 1)
        interactive = inter;
    return (interactive);
}

/**
Control D out of cat
 */
void	ft_signal_exit(t_data *data, t_cmds *cmds)
{
	free(cmds->prompt);
	ft_doublefree(data->env);
	write(1, "exit\n", 5);
	exit(0);
}

/**
 * SIGINT = control C
 */
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
        write(1, "\n", 1);
        rl_on_new_line();
        //rl_replace_line("", 0);
        rl_redisplay();
    }
}

/**
 * @param SIGINT = control C inside Cat
 * @param SIGQUIT = control
 */
void	signal_handler(int signal)
{
    if (ft_interactive(-1) == 1)
        interact_signal(signal);
    else if (ft_interactive(-1) == 0)
    {
        if (signal == SIGQUIT)
        {
            ft_interactive(1);
            write(1, "Quit\n", 5);
            rl_on_new_line();
        }
        else if (signal == SIGINT)
        {
            ft_interactive(1);
            write(1, "\n", 1);
            rl_on_new_line();
        }
    }
    else
        printf("%d signal", signal);
}

void	ft_signals(void)
{
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
}