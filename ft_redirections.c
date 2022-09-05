/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:38:49 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/05 18:58:48 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int	heredoc_loop(int *fd, t_env *envar, t_args *here)
{
	char	*heredoc;

	while (1)
	{
		heredoc = readline("> ");
		if (!heredoc)
		{
			free(heredoc);
			close ((*fd));
			return (1);
		}
		else if (!ft_strcmp(heredoc, *here->arg))
		{
			free(heredoc);
			close ((*fd));
			return (1);
		}
		else if (heredoc[0] == '$')
			heredoc = ft_getvalue(envar, &heredoc[1]);
		ft_putendl_fd(heredoc, (*fd));
	}
	return (0);
}

static int	ft_document(t_env *envar, t_args *here)
{
	int	status;
	int	pid;
	int	fd;

	pid = fork();
	g_mode.g_sig = 1;
	fd = open("/tmp/tmpfile", O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (pid == 0)
	{
		g_mode.g_sig = 2;
		if (heredoc_loop(&fd, envar, here))
			exit(0);
		close (fd);
		exit(0);
	}
	waitpid(pid, &status, 0);
	close(fd);
	g_mode.g_sig = 0;
	if (status == 0)
		return (open("/tmp/tmpfile", O_RDONLY, 0644));
	else
	{
		g_mode.g_sig = 0;
		return (-1);
	}
}

int	ft_redirection(t_fds *fds, t_exenv exenv)
{
	int	fd;

	fd = 0;
	init_fds(&fds);
	while (exenv.args)
	{
		if (exenv.args && exenv.args->type == HEREDOC)
		{
			fd = ft_document(exenv.env, exenv.args);
			g_mode.g_sig = 0;
			if (fd == -1)
				return (1);
			ft_fdadd_back(&fds->here_f, ft_lstnewfd(fd));
		}
		else if (exenv.args && exenv.args->type == OUT)
			ft_fdadd_back(&fds->out_f, ft_lstnewfd(ft_openout(exenv.args)));
		else if (exenv.args && exenv.args->type == APPEND)
			ft_fdadd_back(&fds->app_f, ft_lstnewfd(ft_append(exenv.args)));
		else if (exenv.args && exenv.args->type == IN)
			ft_fdadd_back(&fds->in_f, ft_lstnewfd(ft_openin(exenv.args)));
		exenv.args = exenv.args->next;
	}
	return (0);
}
