#include "../../include/minishell.h"

bool	ft_next_next_errors(int errnumb)
{
	if (errnumb == 8)
	{
		fprintf(stderr, "ERR : FINAL PIPE\n");
		return (true);
	}
	else if (errnumb == 10)
	{
		fprintf(stderr, "ERR : REDDIRECTION ERROR\n");
		return (true);
	}
	else if (errnumb == 12)
	{
		fprintf(stderr, "ERR : EMPTY PIPE\n");
		return (true);
	}
	return (false);
}

bool	ft_next_errors(int errnumb)
{
	if (errnumb == 5)
	{
		fprintf(stderr, "ERR : QUOTATION\n");
		return (true);
	}
	else if (errnumb == 7)
	{
		fprintf(stderr, "ERR : INVALIDCHR\n");
		return (true);
	}
	else if (errnumb == 9)
	{
		fprintf(stderr, "ERR : Command not found\n");
		return (true);
	}
	if (ft_next_next_errors(errnumb))
		return (true);
	return (false);
}

bool	ft_error_print(int errnumb)
{
	if (errnumb == 2)
	{
		fprintf(stderr, "ERR : NOTWANNAHANDLE\n");
		return (true);
	}
	else if (errnumb == 3)
	{
		fprintf(stderr, "ERR : SIGSMTHG\n");
		return (true);
	}
	else if (errnumb == 4)
	{
		fprintf(stderr, "ERR : UNDEFINED\n");
		return (true);
	}
	else if (errnumb == 6)
	{
		fprintf(stderr, "ERR : UKNOWN\n");
		return (true);
	}
	if (ft_next_errors(errnumb))
		return (true);
	return (false);
}

void	ft_free_commands(t_command_table *table)
{
	int	i;

	i = -1;
	while (++i < table->cmd_count && table->cmd_count)
	{
		if (table->commands[i].command)
			ft_doublefree(table->commands[i].command);
		table->commands[i].command = NULL;
		if (table->commands[i].bin_path)
		{
			free(table->commands[i].bin_path);//TODO:si metes el espacio raro lo que peta es esto de aqui
		}
		table->commands[i].bin_path = NULL;
	}
	if (!table->commands)
		return ;
	free(table->commands);
}

bool	ft_check_errors(char *str)
{
	str = added_pipe(str);
	if (str == NULL || !(ft_strlen(str) > 0))//TODO: WTF
	{
		ft_error_print(11);
		if (str)
			free(str);
		return (1);
	}	
	return (0);
}
