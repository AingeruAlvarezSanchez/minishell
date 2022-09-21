#include "../../include/minishell.h"

bool	ft_next_next_errors(int error)
{
	if (error == 8)
	{
		fprintf(stderr, "ERR : FINAL PIPE\n");
		return (1);
	}
	else if (error == 10)
	{
		fprintf(stderr, "ERR : REDDIRECTION ERROR\n");
		return (1);
	}
	else if (error == 12)
	{
		fprintf(stderr, "ERR : EMPTY PIPE\n");
		return (1);
	}
	return (0);
}

bool	ft_next_errors(int error)
{
	if (error == 5)
	{
		fprintf(stderr, "ERR : QUOTATION\n");
		return (1);
	}
	else if (error == 7)
	{
		fprintf(stderr, "ERR : INVALIDCHR\n");
		return (1);
	}
	else if (error == 9)
	{
		fprintf(stderr, "ERR : Command not found\n");
		return (1);
	}
	if (ft_next_next_errors(error))
		return (1);
	return (0);
}

bool	ft_print_err(int error)
{
	if (error == 2)
	{
		fprintf(stderr, "ERR : NOTWANNAHANDLE\n");
		return (1);
	}
	else if (error == 3)
	{
		fprintf(stderr, "ERR : SIGSMTHG\n");
		return (1);
	}
	else if (error == 4)
	{
		fprintf(stderr, "ERR : UNDEFINED\n");
		return (1);
	}
	else if (error == 6)
	{
		fprintf(stderr, "ERR : UKNOWN\n");
		return (1);
	}
	if (ft_next_errors(error))
		return (1);
	return (0);
}

void	ft_free_commands(t_cmds_all *cmds)
{
	int	i;

	i = -1;
	while (++i < cmds->n_cmds && cmds->n_cmds)
	{
		if (cmds->cmds[i].cmd)
			ft_doublefree(cmds->cmds[i].cmd);
        cmds->cmds[i].cmd = NULL;
		if (cmds->cmds[i].bin_pth)
		{
			free(cmds->cmds[i].bin_pth);
		}
        cmds->cmds[i].bin_pth = NULL;
	}
	if (!cmds->cmds)
		return ;
	free(cmds->cmds);
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
