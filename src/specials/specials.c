#include "../../include/minishell.h"


/**
 * @param tmp
 * @param x
 * @param next
 * @param cmd
 * @return
 */
char	**ft_not_prev(char *tmp, int x, int next, t_cmd *cmd)
{
	char	**com;

	com = (char **)malloc(sizeof(char *) * 3);
	com[0] = ft_strdup(tmp);
	com[1] = ft_substr(cmd->cmd[x], (next + 1),
					ft_strlen(cmd->cmd[x]) - (next + 1));
	com[2] = 0;
	free(cmd->cmd[x]);
	if (!com[0][0] && !com[1][0])
		cmd->cmd[x] = ft_strdup("");
	else
		cmd->cmd[x] = ft_strjoin(com[0], com[1]);
	return (com);
}

void	ft_trim_quot(t_cmd *cmd, int x, int next, int y)
{
	char	*prev;
	char	**str;
	char	*aux;

	prev = ft_substr(cmd->cmd[x], 0, y);
	aux = ft_substr(cmd->cmd[x], (y + 1), (next - (y + 1)));
	if (prev[0])
	{
		str = (char **)malloc(sizeof(char *) * 4);
		str[0] = ft_strdup(prev);
		str[1] = ft_strdup(aux);
		free(aux);
		str[2] = ft_substr(cmd->cmd[x], (next + 1), ft_strlen(cmd->cmd[x]) - (next + 1));
		str[3] = 0;
		aux = ft_strjoin(str[0], str[1]);
		free(cmd->cmd[x]);
		cmd->cmd[x] = ft_strjoin(aux, str[2]);
	}
	else
		str = ft_not_prev(aux, x, next, cmd);
	ft_doublefree(str);
	free(prev);
	free(aux);
}

void	ft_trim_algorithm(t_cmd *cmd, int x)
{
	int		next;
	int		y;

    y = 0;
	while (cmd->cmd[x][y])
	{
		if (cmd->cmd[x][y] == '"' || cmd->cmd[x][y] == '\'')
		{
            next = y + 1;
			while (cmd->cmd[x][next] && cmd->cmd[x][next]
                                        != cmd->cmd[x][y])
				next++;
            ft_trim_quot(cmd, x, next, y);
			if (next >= ft_strlen(cmd->cmd[x]))
				return ;
            y = next - 1;
			continue ;
		}
		y++;
	}
}

/**
 * @param cmd string with cmd
 * @return true if has redir
 */
bool	ft_has_redir(char *cmd)
{
    if (ft_str_has(cmd, "<<"))
        return (true);
    if (ft_str_has(cmd, ">>"))
        return (true);
    if (ft_str_has(cmd, "<"))
        return (true);
    if (ft_str_has(cmd, ">"))
        return (true);
    return (false);
}

/**
 * @param prompt string taken from prompt
 * @return null if syntax error
 */
char	*ft_pipe_add(char *prompt)
{
    if (prompt[0] == '|')
    {
        printf("Ejemplo₺: sytax error near unexpected token '|'\n");
        prompt = NULL;
    }
    if (ft_last_nopipe(prompt))
    {
        while (ft_last_nopipe(prompt))
        {
            if (ft_strlen(prompt) > 1)
                prompt = ft_strjoin(prompt, readline("> "));
            else
                prompt = readline("> ");
        }
    }
    return (prompt);
}