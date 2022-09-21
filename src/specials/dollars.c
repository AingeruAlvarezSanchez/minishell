#include "../../include/minishell.h"

/**
 * @param cmd struct with command
 * @param dollar struct with dollar data
 * @param x variable pos
 * @param ref reference position
 */
static void	ft_has_beg(t_dollar *dollar, t_cmd *cmd, int x, int xref)
{
	if (dollar->val)
		ft_valuebeg(dollar, cmd, x, xref);
	else if (xref < ft_strlen(cmd->cmd[x]) || cmd->cmd[x][xref - 1] == '"')
        dollar->final = ft_strjoin(dollar->pre, dollar->last);
	else
        dollar->final = ft_strjoin(dollar->pre, "");
}

/**
 * @param cmd struct with command
 * @param dollar struct with dollar data
 * @param x variable pos
 * @param ref reference position
 */
static void	ft_new_com(t_dollar *dollar, t_cmd *cmd, int x, int xref)
{
	if (dollar->pre[0])
		ft_has_beg(dollar, cmd, x, xref);
	else
	{
		if (dollar->val)
		{
			free(dollar->pre);
            dollar->pre = ft_strdup(dollar->val);
			if (xref < ft_strlen(cmd->cmd[x]))
                dollar->final = ft_strjoin(dollar->pre, dollar->last);
			else
                dollar->final = ft_strdup(dollar->pre);
		}
		else if (dollar->last != NULL)
            dollar->final = ft_strjoin("", dollar->last);
	}
	free(cmd->cmd[x]);
    cmd->cmd[x] = ft_strdup(dollar->final);
}

/**
 * @param cmd struct with command
 * @param dollar struct with dollar data
 * @param x variable pos
 * @param ref reference position
 */
void	ft_check_exceptions(t_cmd *cmd, t_dollar *dollar, int x, int xref)
{
	if (ft_check_char(cmd, x, xref, "$?@/:")
		&& (cmd->cmd[x][xref - 1] == '$'))
        dollar->last = ft_substr(cmd->cmd[x], (xref + 1),
                                 (ft_strlen(cmd->cmd[x]) - (xref + 1)));
	else
        dollar->last = ft_substr(cmd->cmd[x], xref,
                                 (ft_strlen(cmd->cmd[x]) - xref));
}

/**
 * @param cmd struct with command
 * @param env struct with environment
 * @param x variable pos
 * @param xref reference position
 */
void	ft_dollar_expansion(t_cmd *cmd, t_env *env, int x, int xref)
{
	t_dollar	dollar;

    dollar.val = ft_dollar_value(cmd, env, x, xref);
    dollar.pre = ft_substr(cmd->cmd[x], 0, xref);
	xref++;
	if (cmd->cmd[x][xref] != '$')
	{
		while (cmd->cmd[x][xref] &&
               !ft_check_char(cmd, x, xref, " \'$?@/:"))
			xref++;
	}
	else
		xref++;
	if (xref < ft_strlen(cmd->cmd[x])
        || cmd->cmd[x][xref - 1] == '"')
	{
		if (xref < ft_strlen(cmd->cmd[x]))
			ft_check_exceptions(cmd, &dollar, x, xref);
		else if (cmd->cmd[x][xref - 1] == '"')
            dollar.last = ft_strdup("\"");
	}
	else
        dollar.last = ft_strdup("");
	ft_new_com(&dollar, cmd, x, xref);
    ft_struct_free(&dollar);
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
