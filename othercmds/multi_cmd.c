/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:55:12 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/04 22:32:51 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_multicmd(t_vars *vars, t_exenv exenv, t_fds	*fds)
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
	if (fds->new_in == 0)
	{
		close(vars->fd[1]);
		dup2(vars->fd[0], STDIN_FILENO);
		close(vars->fd[0]);
	}
	return (0);
}

void	check_multired(t_exenv *exenv, t_fds	**fds)
{
	if (exenv->args->type == OUT)
	{
		(*fds)->new_out = (*fds)->out_f->next->fd;
		if ((*fds)->out_f->next)
			(*fds)->out_f = (*fds)->out_f->next;
	}
	else if (exenv->args->type == APPEND)
	{
		(*fds)->new_out = (*fds)->app_f->next->fd;
		if ((*fds)->app_f->next)
			(*fds)->app_f = (*fds)->app_f->next;
	}
	else if (exenv->args->type == IN)
	{
		(*fds)->new_in = (*fds)->in_f->next->fd;
		if ((*fds)->in_f->next)
			(*fds)->in_f = (*fds)->in_f->next;
	}
	else if (exenv->args->type == HEREDOC)
	{
		(*fds)->new_in = (*fds)->here_f->next->fd;
		if ((*fds)->here_f->next)
			(*fds)->here_f = (*fds)->here_f->next;
	}
}

void	abs_path(t_vars	*vars, t_exenv *exenv)
{
	vars->path = exenv->args->arg[0];
	vars->cmd = get_cmd(exenv->args->arg);
}

void	check_multicmd(t_exenv *exenv, t_fds	**fds, t_vars	*vars)
{
	if (exenv->args->type == COMMAND)
	{
		if (access(exenv->args->arg[0], X_OK) == 0)
			abs_path(vars, exenv);
		else
		{
			if (exenv->args->arg[0][0] == '.'
				&& exenv->args->arg[0][1] == '/')
			{
				vars->path = get_path2(exenv->env, exenv->args->arg);
				if (!ft_strcmp(exenv->args->arg[0], "./minishell"))
					increase_shlvl((*exenv));
			}
			else
				vars->path = get_path(exenv->env, exenv->args->arg);
			vars->cmd = exenv->args->arg;
		}
		execute_multicmd(vars, (*exenv), (*fds));
		free(vars->path);
		(*fds)->new_out = 1;
		(*fds)->new_in = 0;
		vars->i++;
	}
}

void	parse_multicmd(t_exenv exenv, t_fds	*fds)
{
	t_vars	vars;
	int		tmp1;
	int		tmp2;
	int		status;

	exenv.new_env = get_newenv(exenv.env);
	vars.num = cmd_num(exenv.args);
	vars.i = 1;
	tmp1 = dup(1);
	tmp2 = dup(0);
	while (exenv.args)
	{
		check_multired(&exenv, &fds);
		check_multicmd(&exenv, &fds, &vars);
		exenv.args = exenv.args->next;
	}
	while (vars.num--)
		wait(&status);
	if (WIFEXITED(status))
		g_mode.g_exit = WEXITSTATUS(status);
	dup2(tmp1, 1);
	close(tmp1);
	dup2(tmp2, 0);
	close(tmp2);
}
