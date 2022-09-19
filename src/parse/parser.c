#include "../../include/minishell.h"

bool	ft_last_nopipe(char *prompt)
{
	int		i;
	char	last;

	i = 0;
    last = ' ';
	if (prompt != NULL)
	{
		while (prompt[i])
		{
			if (prompt[i] != 32)
                last = prompt[i];
			i++;
		}
	}
	if (last == '|')
		return (true);
	return (false);
}

int	ft_n_pipes(char *prompt)
{
	int	i;
	int	quote;
	int	n_pipes;

	i = 0;
    n_pipes = 0;
	while (i < ft_strlen(prompt) && prompt[i])
	{
		if (prompt[i] == 34 || prompt[i] == 39)
		{
			quote = prompt[i];
			i++;
			while (prompt[i] && prompt[i] != quote)
				i++;
		}	
		if (prompt[i] == 124)
			n_pipes++;
		i++;
	}
	return (n_pipes);
}

bool	ft_create_cmds(char *prompt, int n_cmds, t_cmds_all *cmds)
{
	int			i;
	char		**split;

	i = 0;
    cmds->cmds = (t_cmd *)malloc(sizeof(t_cmd) * n_cmds);
	split = mini_split(prompt, '|');
	while (split[i])
	{	
		if (check_if_empty_command(split[i]))
			return (true);
		if (ft_has_redir(split[i]))
			return (true);
        cmds->cmds[i].cmd = mini_split(split[i], ' ');
		i++;
	}
	ft_doublefree(split);
	return (false);
}

/* Cleans de prompt and puts in to cmd cmds */
int	ft_parser(char *prompt, t_cmds_all *cmds)
{
	int		n_cmds;

	if (ft_last_nopipe(prompt))
		return (8);
	if (ft_process_quotes(prompt))
		return (5);
	if (clean_double_pipes(prompt))
		return (5);
    n_cmds = ft_n_pipes(prompt) + 1;
	if (ft_create_cmds(prompt, n_cmds, cmds))
		return (12);
    cmds->n_cmds = n_cmds;
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
