#include "../../include/minishell.h"

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
