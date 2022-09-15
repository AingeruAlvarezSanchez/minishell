#include "../include/minishell.h"
#include <termios.h>

int	lexer(t_command_table *table, t_msh_var *msh)
{
	int	i;
	int	x;

	i = -1;
	while (++i < table->cmd_count)
	{
		x = 0;
		while (table->commands[i].command[x])
		{
			if (ft_check_dollars(table, i, x, msh))
			{
				x = 0;
				continue ;
			}
			x++;
		}
		if (contains_redire(table->commands[i].command[x]))
			return (10);
	}
	return (1);
}

bool	ft_start_program(char *str, t_command_table *table, t_msh_var *msh)
{
	if (ft_check_errors(str))
		return (1);
	if (!ft_error_print(parser(str, table)))
	{
		if (!ft_error_print(lexer(table, msh)))
		{
			execute(table, msh);
			return (0);
		}
	}
	return (1);
}

bool	ft_readline(t_msh_var *msh, t_command_table *table, char *str)
{
	struct termios	ter;
	struct termios	prev;

	tcgetattr(STDIN_FILENO, &prev);
	tcgetattr(STDIN_FILENO, &ter);
	ter.c_lflag &= ~(ECHOCTL | ICANON);
	if (ft_strlen(str) > 0)
	{
		if (ft_start_program(str, table, msh))
			return (1);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &prev);
	if (str != NULL)
		free(str);
	return (0);
}

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv, char **environ)
{
    char			*str;
    char			*tmp;
    t_command_table	table;
    t_msh_var		var;

    var.own_envp = ft_duplicate_environment(environ);
    g_exit_status = 0;
    while (1)
    {
        ft_signals();
        if (!(tmp = readline("Ejemplo₺ ")))
            ft_signal_exit();
        if (!tmp[0])
        {
            free(tmp);
            continue ;
        }// TODO:aqui hay error con espacio raro + ls
        str = ft_strtrim(tmp, " ");
        free(tmp);
        add_history(str);
        if (ft_readline(&var, &table, str))
            continue ;
    }
    return (0);
}
