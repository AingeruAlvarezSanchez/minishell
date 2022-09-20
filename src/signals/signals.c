#include "../../include/minishell.h"

/**
Control D out of cat
 */
void	ft_signal_exit(void)
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
		//printf ("^\\Quit: 3\n");TODO:
	else if (signal == SIGINT)
        printf ("\n");
}

void	ft_check_signal(void)
{
	signal(SIGINT, ft_interactive);
	signal(SIGQUIT, ft_interactive);
}

/**
 * SIGINT = control C out of cat
 */
void	signal_manager(int signal)
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
	signal(SIGINT, signal_manager);
	signal(SIGQUIT, SIG_IGN);
}
