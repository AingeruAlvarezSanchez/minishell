/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:59:54 by aalvarez          #+#    #+#             */
/*   Updated: 2022/09/04 19:15:55 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_create_pipes(t_cmds *cmds) // TODO: mover a otro sitio
{
    cmds->pipefd = (int **)malloc(sizeof(int *) * 2);
    cmds->pipefd[0] = (int *)malloc(sizeof(int) * 2);
    cmds->pipefd[1] = (int *)malloc(sizeof(int) * 2);
}

int until_pipe(char ** tokens, int a)
{
    while(tokens[a])
    {
        if(tokens[a][0] == '|')
            break;
        a++;
    }
    return a;
}

int	ft_pipes(t_cmds *cmds, int xref)
{
	char	**tmp3;
	int		i;

	tmp3 = ft_doublestrdup(cmds->tokens);
	ft_doublefree(cmds->tokens);
	if (!tmp3)
	{
		cmds->tokens = (char **)malloc(sizeof(char *) * 3);
		cmds->tokens[0] = ft_substr(cmds->prompt, 0, xref);
		cmds->tokens[1] = ft_strdup("|");
		cmds->tokens[2] = 0;
	}
	else
	{
		i = -1;
		cmds->tokens = (char **)malloc(sizeof(char *)
				* (ft_doublestrlen(tmp3) + 3));
		while (tmp3[++i])
			cmds->tokens[i] = ft_strdup(tmp3[i]);
		cmds->tokens[i] = ft_substr(cmds->prompt, 0, xref);
		cmds->tokens[i + 1] = ft_strdup("|");
		cmds->tokens[i + 2] = 0;
	}
	return (ft_doublefree(tmp3), xref + 1);
}
