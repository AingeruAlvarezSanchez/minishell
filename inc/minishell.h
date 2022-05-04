#ifndef MINISHELL_H
#define MINISHELL_H
# include "../libft/libft.h"

typedef struct s_data {
    char    **env;
    char    **paths;
}   t_data;

typedef struct s_cmds {
    char    **tokens;
    int     n_cmds;
}   t_cmds;

typedef struct s_proc {
    char    *binary;
    char    *flags;
    char    *command;
}   t_proc;

/* Inital checks and memory allocation functions */
void    ft_cpyenv(t_data *data, char **envp);
void    ft_initcmds(char *prompt, t_cmds *cmds);

/* Functions to check various errors */
int     ft_has_final(t_cmds *cmds, int iref, int jref, int c);
int     ft_pipes_error(t_cmds *cmds, int iref, int jref);
void    ft_nonulls(t_cmds *cmds);

/* Functions to manage special characters*/
int	    ft_has_special_char(t_cmds *cmds);
void	ft_newcmds(t_cmds *cmds, char **tmp);

/* Quote managing functions */
void    ft_quotes(t_cmds *cmds, int iref, int jref, int xref);

/* Pipes managing functions */
int     ft_check_pipes(t_cmds *cmds, int iref, int jref);

/* Dollar managing functions */
void    ft_check_metacharacter(t_cmds *cmds, t_data *data);
void    ft_check_dollar(t_cmds *cmds, t_data *data, int iref, int jref);

#endif