/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:55:12 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/25 02:47:45 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	processing_firstcmd(char *path, t_exenv exenv, int *fd)
{
	// dup2(vars->f1, STDIN_FILENO);
	// close(fd[0]);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    if(!ft_strcmp(exenv.args->arg[0], "cd") || !ft_strcmp(exenv.args->arg[0], "pwd")
        || !ft_strcmp(exenv.args->arg[0], "env") || !ft_strcmp(exenv.args->arg[0], "echo")
        || !ft_strcmp(exenv.args->arg[0], "export") || !ft_strcmp(exenv.args->arg[0], "unset"))
        ft_builtins(exenv);
    else
    {
        if (execve(path, exenv.args->arg, exenv.envar) == -1)
            write(2, "execve Error!", 14);
    }
	exit(EXIT_FAILURE);
}

void	processing_mdlcmd(char *path, t_exenv exenv, int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
    if(!ft_strcmp(exenv.args->arg[0], "cd") || !ft_strcmp(exenv.args->arg[0], "pwd")
        || !ft_strcmp(exenv.args->arg[0], "env") || !ft_strcmp(exenv.args->arg[0], "echo")
        || !ft_strcmp(exenv.args->arg[0], "export") || !ft_strcmp(exenv.args->arg[0], "unset"))
        ft_builtins(exenv);
    else
    {
        if (execve(path, exenv.args->arg, exenv.envar) == -1)
            write(2, "execve Error!", 14);
    }
	exit(EXIT_FAILURE);
}

void	processing_lastcmd(char *path, t_exenv exenv, int *fd)
{
	// dup2(vars->f2, STDOUT_FILENO);
	close(fd[0]);
    dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
    if(!ft_strcmp(exenv.args->arg[0], "cd") || !ft_strcmp(exenv.args->arg[0], "pwd")
        || !ft_strcmp(exenv.args->arg[0], "env") || !ft_strcmp(exenv.args->arg[0], "echo")
        || !ft_strcmp(exenv.args->arg[0], "export") || !ft_strcmp(exenv.args->arg[0], "unset"))
        ft_builtins(exenv);
    else
    {
        if (execve(path, exenv.args->arg, exenv.envar) == -1)
            write(2, "execve Error!", 14);
    }
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

int    execute_multicmd(t_vars *vars, t_exenv exenv, int *fd)
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
			processing_firstcmd(vars->path, exenv, fd);
            printf("First %s\n",exenv.args->arg[0]);
            // exit(1);
        }
		else if (vars->i == (vars->num))
        {
			processing_lastcmd(vars->path, exenv, fd);
            printf("Last  %s\n", exenv.args->arg[0]);
            // exit(1);
        }
		else
        {
			processing_mdlcmd(vars->path, exenv, fd);
            printf("Middle %s\n", exenv.args->arg[0]);
            // exit(1);
        }
	}
    waitpid(pid1,NULL,0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	return (0);
}

void    parse_multicmd(t_exenv exenv)
{
    t_vars  vars;

    // vars = malloc(sizeof(t_args *));

    vars.num = cmd_num(exenv.args);
    printf("-----%d----\n", vars.num);
    vars.i = 1;
    while(exenv.args)
    {
        if (exenv.args->type == COMMAND)
		{
            vars.path = get_path(exenv.env, exenv.args->arg);
            execute_multicmd(&vars, exenv, vars.fd);
            free(vars.path);
            vars.i++;
        }
		exenv.args = exenv.args->next;
    }
}