/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:55:12 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/26 18:23:21 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	processing_firstcmd(t_vars *vars, t_exenv exenv, int *fd, t_fds	*fds)
{
	// dup2(vars->f1, STDIN_FILENO);
	// close(fd[0]);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    if(!ft_strcmp(exenv.args->arg[0], "cd") || !ft_strcmp(exenv.args->arg[0], "pwd")
        || !ft_strcmp(exenv.args->arg[0], "env") || !ft_strcmp(exenv.args->arg[0], "echo")
        || !ft_strcmp(exenv.args->arg[0], "export") || !ft_strcmp(exenv.args->arg[0], "unset"))
        ft_builtins(exenv, fds);
    else
    {
        if (execve(vars->path, vars->cmd, exenv.envar) == -1)
            write(2, "execve Error!", 14);
    }
	exit(EXIT_FAILURE);
}

void	processing_mdlcmd(t_vars *vars, t_exenv exenv, int *fd, t_fds	*fds)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
    if(!ft_strcmp(exenv.args->arg[0], "cd") || !ft_strcmp(exenv.args->arg[0], "pwd")
        || !ft_strcmp(exenv.args->arg[0], "env") || !ft_strcmp(exenv.args->arg[0], "echo")
        || !ft_strcmp(exenv.args->arg[0], "export") || !ft_strcmp(exenv.args->arg[0], "unset"))
        ft_builtins(exenv, fds);
    else
    {
        if (execve(vars->path, vars->cmd, exenv.envar) == -1)
            write(2, "execve Error!", 14);
    }
	exit(EXIT_FAILURE);
}

void	processing_lastcmd(t_vars *vars, t_exenv exenv, int *fd, t_fds	*fds)
{
	// dup2(vars->f2, STDOUT_FILENO);
	close(fd[0]);
    dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
    if(!ft_strcmp(exenv.args->arg[0], "cd") || !ft_strcmp(exenv.args->arg[0], "pwd")
        || !ft_strcmp(exenv.args->arg[0], "env") || !ft_strcmp(exenv.args->arg[0], "echo")
        || !ft_strcmp(exenv.args->arg[0], "export") || !ft_strcmp(exenv.args->arg[0], "unset"))
        ft_builtins(exenv, fds);
    else
    {
        if (execve(vars->path, vars->cmd, exenv.envar) == -1)
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

int    execute_multicmd(t_vars *vars, t_exenv exenv, int *fd, t_fds	*fds)
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
			processing_firstcmd(vars, exenv, fd, fds);
            printf("First %s\n",exenv.args->arg[0]);
            // exit(1);
        }
		else if (vars->i == (vars->num))
        {
			processing_lastcmd(vars, exenv, fd, fds);
            printf("Last  %s\n", exenv.args->arg[0]);
            // exit(1);
        }
		else
        {
			processing_mdlcmd(vars, exenv, fd, fds);
            printf("Middle %s\n", exenv.args->arg[0]);
            // exit(1);
        }
	}
    waitpid(pid1,NULL,0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	return (0);
}

void    parse_multicmd(t_exenv exenv, t_fds	*fds)
{
    t_vars  vars;

    vars.num = cmd_num(exenv.args);
    printf("-----%d----\n", vars.num);
    vars.i = 1;
    while(exenv.args)
    {
        if (exenv.args->type == COMMAND)
		{
            if(access(exenv.args->arg[0], X_OK) == 0)
            {
                vars.path = exenv.args->arg[0];
                vars.cmd = get_cmd(exenv.args->arg);
            }
            else
            {
                if(exenv.args->arg[0][0] == '.' && exenv.args->arg[0][1] == '/')
                {
                    vars.path = get_path2(exenv.env, exenv.args->arg);
                    if(!ft_strcmp(exenv.args->arg[0], "./minishell"))
                        increase_shlvl(exenv);
                }
                else
                    vars.path = get_path(exenv.env, exenv.args->arg);
                vars.cmd = exenv.args->arg;
            }
            execute_multicmd(&vars, exenv, vars.fd, fds);
            free(vars.path);
            vars.i++;
        }
		exenv.args = exenv.args->next;
    }
}