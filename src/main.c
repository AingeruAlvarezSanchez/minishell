/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:06:39 by aalvarez          #+#    #+#             */
/*   Updated: 2022/03/29 16:53:05 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

/* need to search for a way to make this function smaller to norminette */

/* This functions searchs for every separator and metacharacter needed for the correct
functioning of the shell, it makes sure cmds->tokens is correctly separated for later
treatment */
void	ft_commands(char *prompt, t_cmds *cmds, __attribute__((unused)) t_data *data)
{
	int	i;
	int	j;
	
	ft_initials(cmds, data, prompt);
	i = -1;
	while (cmds->tokens[++i])
	{
		j = -1;
		while (cmds->tokens[i][++j])
		{
			if (cmds->tokens[i][j] == '\'')
			{
				j = ft_quote_error(cmds, i, (j + 1), 0);
				if (j == -1)
					return ;
				ft_quotes(cmds, data, i, j, 0);
				break ;
			}
			else if (cmds->tokens[i][j] == '"')
			{
				j = ft_quote_error(cmds, i, (j + 1), 1);
				if (j == -1)
					return ;
				ft_quotes(cmds, data, i, j, 1);
				//ft_dollar(cmds, data);
				break ;
			}
			else if (cmds->tokens[i][j] == '|')
				cmds->n_cmds++;
			/*else if (cmds->tokens[i][j] == '$')
			{
				//ft_dollar(cmds, data);
			}*/
		}
	}
	i = -1;
	while (cmds->tokens[++i])
		printf("cmd: %s\n", cmds->tokens[i]);
	printf("Cmd num: %d\n", cmds->n_cmds);
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	t_cmds	cmds;
	t_data	data;

	ft_cpyenv(&data, envp);
	ft_get_path(&data);
	while (1 && argc && argv)
	{	
		prompt = readline("ejemplo1 ₺ ");
		add_history(prompt);
		ft_commands(prompt, &cmds, &data);
		waitpid(cmds.pid, NULL, WUNTRACED);
		free(prompt);
	}
	return (0);
}
