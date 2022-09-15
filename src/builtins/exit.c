#include "../../include/minishell.h"

static void	ft_exit_arg(t_command_table *table, int c_num, int count)
{
	int	i;

	i = 0;
	while (table->commands[c_num].command[1][i])
	{
		if (ft_isalpha(table->commands[c_num].command[1][i]))
		{
			printf("Minishell : %s %s\n",
				table->commands[c_num].command[1],
                ": numeric argument required");
			g_exit_status = 1;
			if (count == 1)
			{
				ft_free_commands(table);
				exit(255);
			}
		}
		i++;
	}
	g_exit_status = ft_atoi(table->commands[c_num].command[1]);
	if (count == 1)
		exit(ft_atoi(table->commands[c_num].command[1]));
}

int	ft_exit(t_command_table *table, int c_num, int count)
{
	int	i;

	if (c_num != count - 1)
		return (1);
	if (count == 1)
		write(1, "exit\n", 5);
	i = 0;
	while (table->commands[c_num].command[i])
		i++;
	if (i > 2)
	{
		printf("Minishell : Too many arguments\n");
		g_exit_status = 1;
		return (0);
	}
	if (table->commands[c_num].command[1])
		ft_exit_arg(table, c_num, count);
	if (count == 1)
	{
		ft_free_commands(table);
		g_exit_status = 0;
		exit(0);
	}
	return (0);
}
