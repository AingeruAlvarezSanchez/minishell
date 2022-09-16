#include "../../include/minishell.h"

bool	last_chr_not_pipe(char *str)
{
	int		i;
	char	last_chr;

	i = 0;
	last_chr = ' ';
	if (str != NULL)
	{
		while (str[i])
		{
			if (str[i] != 32)
				last_chr = str[i];
			i++;
		}
	}
	if (last_chr == '|')
		return (true);
	return (false);
}

int	ft_count_pipes(char *pnt)
{
	int	i;
	int	quote;
	int	pipecount;

	i = 0;
	pipecount = 0;
	while (i < ft_strlen(pnt) && pnt[i])
	{
		if (pnt[i] == 34 || pnt[i] == 39)
		{
			quote = pnt[i];
			i++;
			while (pnt[i] && pnt[i] != quote)
				i++;
		}	
		if (pnt[i] == 124)
			pipecount++;
		i++;
	}
	return (pipecount);
}

bool	generate_command_table(char *str, int cmd_count, t_command_table *table)
{
	int			i;
	char		**split;

	i = 0;
	table->commands = (t_command *)malloc(sizeof(t_command) * cmd_count);
	split = mini_split(str, '|');
	while (split[i])
	{	
		if (check_if_empty_command(split[i]))
			return (true);
		if (contains_redire(split[i]))
			return (true);
		table->commands[i].command = mini_split(split[i], ' ');
		i++;
	}
	ft_doublefree(split);
	return (false);
}

/* Cleans de str and puts in to command table */
int	parser(char *str, t_command_table *table)
{
	int		cmd_nbr;

	if (last_chr_not_pipe(str))
		return (8);
	if (process_string_quotes(str))
		return (5);
	if (clean_double_pipes(str))
		return (5);
	cmd_nbr = ft_count_pipes(str) + 1;
	if (generate_command_table(str, cmd_nbr, table))
		return (12);
	table->cmd_count = cmd_nbr;
	return (1);
}

bool	clean_double_pipes(char *str)
{
    int	i;
    int	bef_char;

    i = 1;
    bef_char = 0;
    while (str[i])
    {
        if (str[i] == '|' && str[bef_char] == '|')
            return (true);
        i++;
        bef_char++;
    }
    return (false);
}
