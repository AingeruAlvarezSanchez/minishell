#include "../../include/minishell.h"

static int	ft_get_pos(int pos, char *raw_cmd)
{
	int	i;

	while (++pos < ft_strlen(raw_cmd))
	{
		if (raw_cmd[pos] == '\'' || raw_cmd[pos] == '"')
		{
            i = pos + 1;
			while (raw_cmd[i])
			{
				if (raw_cmd[i] == raw_cmd[pos])
				{
                    pos = i;
					break ;
				}
				i++;
			}
			if (pos == i)
				continue ;
			return (1);
		}
	}
	return (0);
}

int	ft_process_quotes(char *raw_cmd)
{
	int		pos;

    pos = -1;
	if (!raw_cmd)
        raw_cmd = NULL;
	if (ft_get_pos(pos, raw_cmd))
		return (1);
	return (0);
}

bool	ft_check_null_cmd(char *cmd)
{
    int	i;
    int	c;

    c = 0;
    i = 0;
    if (!cmd)
        return (1);
    while (cmd[c])
    {
        if (cmd[c] <= 32)
            i++;
        c++;
    }
    if (i == ft_strlen(cmd))
        return (1);
    return (0);
}