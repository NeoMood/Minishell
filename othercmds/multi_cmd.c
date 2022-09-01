/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:55:12 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/01 17:42:39 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	processing_firstcmd(t_vars *vars, t_exenv exenv, int *fd, t_fds	*fds)
{
    if(vars->f == 0)
    {
	    close(fd[0]);
	    dup2(fd[1], STDOUT_FILENO);
    }
    if(!ft_check_builtins(exenv))
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
    if(vars->f == 0)
    {
	    close(fd[0]);
	    dup2(fd[1], STDOUT_FILENO);
    }
    if(!ft_check_builtins(exenv))
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
    (void)fd;
    if(!ft_check_builtins(exenv))
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

int    execute_multicmd(t_vars *vars, t_exenv exenv, t_fds	*fds)
{
    int	pid1;

	if (pipe(vars->fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (1);
	if (pid1 == 0)
	{
		if (vars->i == 1)
			processing_firstcmd(vars, exenv, vars->fd, fds);
		else if (vars->i == (vars->num))
			processing_lastcmd(vars, exenv, vars->fd, fds);
		else
			processing_mdlcmd(vars, exenv, vars->fd, fds);
	}
	close(vars->fd[1]);
	dup2(vars->fd[0], STDIN_FILENO);
    close(vars->fd[0]);
	return (0);
}

void    parse_multicmd(t_exenv exenv, t_fds	*fds)
{
    t_vars  vars;

    vars.num = cmd_num(exenv.args);
    vars.i = 1;
    vars.f = 0;
    int tmp;
    int tmp2;
    int status;

    // status = 0;
    tmp = dup(1);
    tmp2 = dup(STDIN_FILENO);
    while(exenv.args)
    {
        if((exenv.args->type == OUT && exenv.args->next->type == OUT))
        {
            dup2(fds->out_f->next->fd, STDOUT_FILENO);
            close(fds->out_f->next->fd);
            fds->out_f = fds->out_f->next;
            exenv.args = exenv.args->next;
            vars.f = 1;
        }
        else if(exenv.args->type == OUT && exenv.args->next->type == COMMAND)
        {
            dup2(fds->out_f->next->fd, STDOUT_FILENO);
            close(fds->out_f->next->fd);
            fds->out_f = fds->out_f->next;
            exenv.args = exenv.args->next;
            vars.f = 1;
        }
        if((exenv.args->type == IN && exenv.args->next->type == IN))
        {
            dup2(fds->in_f->next->fd, STDIN_FILENO);
            close(fds->in_f->next->fd);
            fds->in_f = fds->in_f->next;
            exenv.args = exenv.args->next;
        }
        else if(exenv.args->type == IN && exenv.args->next->type == COMMAND)
        {
            dup2(fds->in_f->next->fd, STDIN_FILENO);
            close(fds->in_f->next->fd);
            exenv.args = exenv.args->next;
        }
        else if(exenv.args->type == HEREDOC)
            exenv.args = exenv.args->next;
        else if(exenv.args->type == APPEND && exenv.args->next->type == APPEND)
        {
            dup2(fds->app_f->next->fd, STDOUT_FILENO);
            close(fds->app_f->next->fd);
            fds->app_f = fds->app_f->next;
            exenv.args = exenv.args->next;
            vars.f = 1;
        }
        else if(exenv.args->type == APPEND && exenv.args->next->type == COMMAND)
        {
            dup2(fds->app_f->next->fd, STDOUT_FILENO);
            close(fds->app_f->next->fd);
            fds->app_f = fds->app_f->next;
            exenv.args = exenv.args->next;
            vars.f = 1;
        }
        else
        {
            if(vars.f == 1)
            {
                dup2(tmp, STDOUT_FILENO);
                close(tmp);
            }
        }
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
            execute_multicmd(&vars, exenv, fds);
            free(vars.path);
            vars.i++;
        }
		exenv.args = exenv.args->next;
    }
    while(vars.num--)
        wait(&status);
    if (wait(&status) != -1)
    {
        if (WIFEXITED(status))
            g_exit = WEXITSTATUS(status);
    }
    dup2(tmp2, STDIN_FILENO);
}