/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:55:12 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/24 16:14:59 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	processing_firstcmd(char *path, char **cmd, char **env, int *fd)
{
	// dup2(vars->f1, STDIN_FILENO);
	// close(fd[0]);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    // if(!ft_strcmp(parse->arg[0], "cd") || !ft_strcmp(parse->arg[0], "pwd")
    //     || !ft_strcmp(parse->arg[0], "env") || !ft_strcmp(parse->arg[0], "echo")
    //     || !ft_strcmp(parse->arg[0], "export") || !ft_strcmp(parse->arg[0], "unset"))
    //     ft_builtins(parse, env, exp);
    // else
    // {
        if (execve(path, cmd, env) == -1)
            write(2, "execve Error!", 14);
    // }
	exit(EXIT_FAILURE);
}

void	processing_mdlcmd(char *path, char **cmd, char **env, int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	if (execve(path, cmd, env) == -1)
		write(2, "execve Error!", 14);
	exit(EXIT_FAILURE);
}

void	processing_lastcmd(char *path, char **cmd, char **env, int *fd)
{
	// dup2(vars->f2, STDOUT_FILENO);
	close(fd[0]);
    dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	if (execve(path, cmd, env) == -1)
		write(2, "execve Error!", 14);
	exit(EXIT_FAILURE);
}

int cmd_num(t_args *args)
{
    int i;
    t_args *clone;

    i = 0;
    clone = args;
    while(clone)
    {
        if (clone->type == COMMAND)
            i++;
        clone = clone->next;
    }
    return(i);
}

int    execute_multicmd(t_vars *vars, char **cmd, char **env, int *fd)
{
    int	pid1;
    // (void)cmd;
    // (void)env;
    // (void)fd;

	if (pipe(vars->fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (1);
	if (pid1 == 0)
	{
		if (vars->i == 1)
        {
			processing_firstcmd(vars->path, cmd, env, fd);
            printf("First %s\n",cmd[0]);
            // exit(1);
        }
		else if (vars->i == (vars->num))
        {
			processing_lastcmd(vars->path, cmd, env, fd);
            printf("Last  %s\n",cmd[0]);
            // exit(1);
        }
		else
        {
			processing_mdlcmd(vars->path, cmd, env, fd);
            printf("Middle %s\n",cmd[0]);
            // exit(1);
        }
	}
    waitpid(pid1,NULL,0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	return (0);
}

void    parse_multicmd(t_args *args, t_env *env, char **envar)
{
    t_vars  vars;

    // vars = malloc(sizeof(t_args *));

    vars.num = cmd_num(args);
    printf("-----%d----\n", vars.num);
    vars.i = 1;
    while(args)
    {
        if (args->type == COMMAND)
		{
            vars.path = get_path(env, args->arg);
            execute_multicmd(&vars, args->arg, envar, vars.fd);
            free(vars.path);
            vars.i++;
        }
		args = args->next;
    }
}