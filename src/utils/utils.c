#include "../../include/minishell.h"

void	ft_strtolower(char *str)
{
    int		i;

    i = 0;
    while (str && str[i])
    {
        str[i] = ft_tolower(str[i]);
        i++;
    }
}

bool	FT_str_contains(const char *cmd, char *str)
{
	int	i;
	int	u;
	int	length;

	i = 0;
	u = 0;
    length = ft_strlen(str);
	while (cmd[i])
	{
		if (cmd[i] == str[u])
		{
			u++;
			if (u == length)
				return (true);
		}
		else
			u = 0;
		i++;
	}
	return (false);
}

bool	ft_str_has(char *cmd, char *str)
{
    int	i;
    int	u;
    int	maxlength;
    int	mlength;

    i = 0;
    u = 0;
    if (!str || !cmd)
        return (false);
    maxlength = ft_strlen(str);
    mlength = ft_strlen(cmd);
    while (cmd[i])
    {
        if (cmd[i] == str[u])
        {
            u++;
            if (u == maxlength && mlength == maxlength)
                return (true);
        }
        else
            u = 0;
        i++;
    }
    return (false);
}

char	*ft_cpy_path(t_cmd *cmd, int pos)
{
    char	*path;

    path = ft_strdup(cmd->path[pos]);
    ft_doublefree(cmd->path);
    return (path);
}

/**
 *
 * @param cmds struct with commands
 * @param pos_cmd actual position of command
 * @param n_cmds number of commands in prompt
 * @param env struct with environment
 * @return 1
 */
bool	ft_final_cmd(t_cmds_all *cmds, int n_cmds, int pos_cmd, t_env *env)
{
    ft_is_exit(cmds, pos_cmd, n_cmds);
    ft_parent_builtin(&cmds->cmds[pos_cmd], env, pos_cmd, pos_cmd);
    ft_free_commands(cmds);
    return (1);
}
