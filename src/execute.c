#include "../inc/minishell.h"

void	ft_child_builtin(char **command, t_data *Data)
{
    if (!command[0])
        return ;
    if (!ft_strncmp(command[0], "pwd", 3))
        ft_pwd();
    else if (!ft_strncmp(command[0], "echo", 4))
        ft_check_echo(command);
    else if (!ft_strncmp(command[0], "env", 3))
        ft_env(Data);
}

/**
 * @brief If the check_parent function returns true, this function
 * is called in order to check what builtin should be called for
 * execution
 *
 * @param cmd_n This is the actual executing command number in
 * all the commands sent by pipes
 */
void	ft_parent_builtin(char** command, t_data *data, int cmd_n, t_cmds *cmds)
{
    if (!command[cmd_n])
        return ;
    if (!ft_strncmp(command[0], "exit", 4)/* && !command[0][4]*/)
        ft_exit(command[1], data, cmd_n, cmds);
    else if (!ft_strncmp(command[0], "cd", 2)/* && !command[2]*/)
        ft_cd(command[1], data, cmd_n);
    else if (!ft_strncmp(command[0], "export", 6)/* && !command[6]*/)
        ft_check_export(command, data, cmd_n);
    else if (!ft_strncmp(command[0], "unset", 5)/* && !command[5]*/)
        ft_check_unset(command, data, cmd_n);
}
/**
 * @brief This function checks wheter the builtins created
 * is a parent or a child builtin
 *
 * @return int If the funcion successes on finding any of the
 * parent builtin names it returns true so the calling function
 * can determine what handler to use
 */
int	ft_check_parent(char *command)
{
    if (!command)
        return (1);
    if (!ft_strncmp(command, "exit", 4) && !command[4])
        return (1);
    else if (!ft_strncmp(command, "cd", 2) && !command[2])
        return (1);
    else if (!ft_strncmp(command, "export", 6)
             && !command[6])
        return (1);
    else if (!ft_strncmp(command, "unset", 5)
             && !command[5])
        return (1);
    return (0);
}

void	ft_execute(t_data *data, char **command, t_cmds *cmds)
{
    char	*tmp;
    int		i;

    i = -1;
    //updatePath(data); //TODO: need to update path before using it
    ft_child_builtin(cmds->command[0], data); //TODO:
    while (data->paths[++i])
    {
        if (access(command[0], X_OK) == 0)
            execve(command[0], command, data->env);
        tmp = ft_strjoin(data->paths[i], command[0]);
        if (access(tmp, X_OK) == 0)
            execve(tmp, command, data->env);
        free(tmp);
    }
    printf("%s: Command not found\n", command[0]);

    exit(0);
}


/**
 * @brief This function creates all the necesary forks
 * in order to execute every command
 *
 * @param pos command number
 */
void	ft_create_forks(t_cmds *cmds, t_data *data, int pos)
{
    cmds->pid = fork();
    ft_interactive(0);
    if (cmds->pid == 0)
    {
        ft_init_execute(cmds, pos);
        close(cmds->pipefd[0][READ]);
        close(cmds->pipefd[0][WRITE]);
        close(cmds->pipefd[1][READ]);
        close(cmds->pipefd[1][WRITE]);
        ft_execute(data, cmds->command[pos], cmds);
    }
}