#include "../inc/minishell.h"


int	ft_ncinstr(char c, char *str)
{
	int	i;
	int q;

	q = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			q++;
		i++;
	}
	return (q);
}

/**
 * @brief Checks if char is inside str and returns position
 * 
 * @param c     this is the char to search
 * @param str   This is the string in which to search for a character
 * @return int  Returns the position of character found or -1
 */
int	ft_cinstr(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief Checks if there is quote and delete them if closed
 * 
 * @param str       This is the string in which to search for quotes
 * @param c         this is the quote type to delete 
 * @return char*    returns string without quotes or str if no coincidence or not closed
 */
int ft_check_quotes(char * str, char c)
{
    int i = -1;
    char * s;
    
    i = ft_cinstr(c, str);
    if(i >= 0)
    {
        s = ft_substr(str, ft_cinstr(c, str), ft_strlen(str + i));
        if (s) 
            return 1;
    }
    return 0;
}

//es inpar
int isOdd(int n)
{
    return n & 1;
}

char *ft_manage_quotes(char * command)
{	
		if(isOdd(ft_ncinstr('\'', command)))
		{
			printf("quotes no cerradas\n");
			return command;
		}

		if(ft_check_quotes(command, '\''))
			return (ft_strtrim(command, "\'"));
		if(ft_check_quotes(command, '\"'))
			return (ft_strtrim(command, "\""));
		return command;

}
