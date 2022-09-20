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

bool	ft_print_err(int error)
{
	if (error == 2)
	{
		fprintf(stderr, "ERR : NOTWANNAHANDLE\n");
		return (true);
	}
	else if (error == 3)
	{
		fprintf(stderr, "ERR : SIGSMTHG\n");
		return (true);
	}
	else if (error == 4)
	{
		fprintf(stderr, "ERR : UNDEFINED\n");
		return (true);
	}
	else if (error == 6)
	{
		fprintf(stderr, "ERR : UKNOWN\n");
		return (true);
	}
	if (ft_next_errors(error))
		return (true);
	return (false);
}

void	ft_free_commands(t_cmds_all *table)
{
	int	i;

	i = -1;
	while (++i < table->n_cmds && table->n_cmds)
	{
		if (table->cmds[i].cmd)
			ft_doublefree(table->cmds[i].cmd);
		table->cmds[i].cmd = NULL;
		if (table->cmds[i].bin_path)
		{
			free(table->cmds[i].bin_path);
		}
		table->cmds[i].bin_path = NULL;
	}
	if (!table->cmds)
		return ;
	free(table->cmds);
}

bool	ft_check_errors(char *prompt)
{
    prompt = ft_pipe_add(prompt);
	if (prompt == NULL || !(ft_strlen(prompt) > 0))//TODO: WTF
	{
        ft_print_err(11);
		if (prompt)
			free(prompt);
		return (1);
	}	
	return (0);
}
