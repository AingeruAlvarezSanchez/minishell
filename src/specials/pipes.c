#include "../../include/minishell.h"

char	*added_pipe(char *str)
{	
	if (str[0] == '|')
	{
		printf("Minishell: sytax error near unexpected token '|'\n");
		str = NULL;
	}
	if (last_chr_not_pipe(str))
	{
		while (last_chr_not_pipe(str))
		{
			if (ft_strlen(str) > 1)
				str = ft_strjoin(str, readline("> "));
			else
				str = readline("> ");
		}
	}
	return (str);
}
