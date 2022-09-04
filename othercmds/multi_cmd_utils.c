/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:30:52 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/04 22:33:57 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	processing_firstcmd(t_vars *vars, t_exenv exenv, int *fd, t_fds	*fds)
{
	if (fds->new_out != 1)
	{
		dup2(fds->new_out, STDOUT_FILENO);
		close(fds->new_out);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
	}
	if (fds->new_in != 0)
	{
		dup2(fds->new_in, STDIN_FILENO);
		close(fds->new_in);
	}
	if (!ft_check_builtins(exenv))
		ft_builtins(exenv, fds);
	else
	{
		if (execve(vars->path, vars->cmd, exenv.new_env) == -1)
			write(2, "execve Error!", 14);
	}
	exit(EXIT_FAILURE);
}

void	processing_mdlcmd(t_vars *vars, t_exenv exenv, int *fd, t_fds	*fds)
{
	if (fds->new_out != 1)
	{
		dup2(fds->new_out, STDOUT_FILENO);
		close(fds->new_out);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
	}
	if (fds->new_in != 0)
	{
		dup2(fds->new_in, STDIN_FILENO);
		close(fds->new_in);
	}
	if (!ft_check_builtins(exenv))
		ft_builtins(exenv, fds);
	else
	{
		if (execve(vars->path, vars->cmd, exenv.new_env) == -1)
			write(2, "execve Error!", 14);
	}
	exit(EXIT_FAILURE);
}

void	processing_lastcmd(t_vars *vars, t_exenv exenv, int *fd, t_fds	*fds)
{
	(void)fd;
	if (fds->new_out != 1)
	{
		dup2(fds->new_out, STDOUT_FILENO);
		close(fds->new_out);
	}
	if (fds->new_in != 0)
	{
		dup2(fds->new_in, STDIN_FILENO);
		close(fds->new_in);
	}
	if (!ft_check_builtins(exenv))
		ft_builtins(exenv, fds);
	else
	{
		if (execve(vars->path, vars->cmd, exenv.new_env) == -1)
			write(2, "execve Error!", 14);
	}
	exit(EXIT_FAILURE);
}

int	cmd_num(t_args *args)
{
	t_args	*clone;
	int		i;

	i = 0;
	clone = args;
	while (clone)
	{
		if (clone->type == COMMAND)
			i++;
		clone = clone->next;
	}
	return (i);
}

int	get_error(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(2, "invalid command!\n", 18);
		g_mode.g_exit = 127;
		return (1);
	}
	else
	{
		while (s[i])
		{
			write(1, &s[i], 1);
			i++;
		}
		write(2, ": No such file or directory\n", 29);
		g_mode.g_exit = 127;
		return (1);
	}
	return (1);
}
