#include "../../include/minishell.h"

static void	ft_has_beg(t_dollars *dollars, t_cmd *cm, int an, int x)
{
	if (dollars->value)
		ft_valuebeg(dollars, cm, an, x);
	else if (x < ft_strlen(cm->cmd[an]) || cm->cmd[an][x - 1] == '"')
		dollars->result = ft_strjoin(dollars->beg, dollars->final);
	else
		dollars->result = ft_strjoin(dollars->beg, "");
}

static void	ft_new_com(t_dollars *dollars, t_cmd *com, int a_n, int xref)
{
	if (dollars->beg[0])
		ft_has_beg(dollars, com, a_n, xref);
	else
	{
		if (dollars->value)
		{
			free(dollars->beg);
			dollars->beg = ft_strdup(dollars->value);
			if (xref < ft_strlen(com->cmd[a_n]))
				dollars->result = ft_strjoin(dollars->beg, dollars->final);
			else
				dollars->result = ft_strdup(dollars->beg);
		}
		else if (dollars->final != NULL)
			dollars->result = ft_strjoin("", dollars->final);
	}
	free(com->cmd[a_n]);
	com->cmd[a_n] = ft_strdup(dollars->result);
}

void	ft_check_exceptions(t_cmd *com, t_dollars *d, int a_n, int xref)
{
	if (ft_check_char(com, a_n, xref, "$?@/:")
		&& (com->cmd[a_n][xref - 1] == '$'))
		d->final = ft_substr(com->cmd[a_n], (xref + 1),
                             (ft_strlen(com->cmd[a_n]) - (xref + 1)));
	else
		d->final = ft_substr(com->cmd[a_n], xref,
                             (ft_strlen(com->cmd[a_n]) - xref));
}

void	ft_dollar_expansion(t_cmd *cmd, t_env *env, int a_n, int xref)
{
	t_dollars	dollars;

	dollars.value = ft_dollar_value(cmd, env, a_n, xref);
	dollars.beg = ft_substr(cmd->cmd[a_n], 0, xref);
	xref++;
	if (cmd->cmd[a_n][xref] != '$')
	{
		while (cmd->cmd[a_n][xref] &&
               !ft_check_char(cmd, a_n, xref, " \'$?@/:"))
			xref++;
	}
	else
		xref++;
	if (xref < ft_strlen(cmd->cmd[a_n])
        || cmd->cmd[a_n][xref - 1] == '"')
	{
		if (xref < ft_strlen(cmd->cmd[a_n]))
			ft_check_exceptions(cmd, &dollars, a_n, xref);
		else if (cmd->cmd[a_n][xref - 1] == '"')
			dollars.final = ft_strdup("\"");
	}
	else
		dollars.final = ft_strdup("");
	ft_new_com(&dollars, cmd, a_n, xref);
    ft_struct_free(&dollars);
}

/**
 *
 * @param cmds struct with commands
 * @param y command pos
 * @param x variable pos
 * @param env struct with environment
 * @return 1 if dollar
 */
bool	ft_check_dollars(t_cmds_all *cmds, int y, int x, t_env *env)
{
	if (ft_strchr_pos(cmds->cmds[y].cmd[x], '$') >= 0
			&& !ft_single_dollar(&cmds->cmds[y], x,
                                 ft_strchr_pos(cmds->cmds[y].cmd[x], '$')))
	{
		if (cmds->cmds[y].cmd[x][0] == '\''
            && cmds->cmds[y].cmd[x][ft_strlen(cmds->cmds[y].cmd[x]) - 1] == '\'')
			return (0);
		ft_dollar_expansion(&cmds->cmds[y], env,
                            x, ft_strchr_pos(cmds->cmds[y].cmd[x], '$'));
		return (1);
	}
	return (0);
}
