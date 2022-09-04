/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:38:49 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/04 15:49:28 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static int	ft_document(t_env *envar, t_args *here)
{
	char	*heredoc;
	int		fd[2];

	if (pipe(fd) == -1)
		perror("pipe");
	mode.g_sig = 2;
	while (1)
	{
		heredoc = readline("> ");
		if (!heredoc)
			return (close(fd[1]), fd[0]);
		if (!ft_strcmp(heredoc, *here->arg) || ft_strlen(heredoc) == 0)
		{
			free (heredoc);
			break ;
		}
		if (heredoc[0] == '$')
			heredoc = ft_getvalue(envar, &heredoc[1]);
		ft_putendl_fd(heredoc, fd[1]);
		free (heredoc);
	}
	close (fd[1]);
	return (fd[0]);
}

static int	ft_openout(t_args *new)
{
	int	out;

	out = open(*(new->arg), O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (out == -1)
		perror(*(new->arg));
	return (out);
}

static int	ft_openin(t_args *new)
{
	int	in;

	in = open(*(new->arg), O_RDONLY, 0777);
	if (in == -1)
		perror(*(new->arg));
	return (in);
}

static int	ft_append(t_args *new)
{
	int	ap;

	ap = open(*(new->arg), O_APPEND | O_CREAT | O_RDWR, 0777);
	if (ap == -1)
		perror(*(new->arg));
	return (ap);
}

void	ft_redirection(t_fds *fds, t_exenv exenv)
{
	fds->in_f = ft_lstnewfd(0);
	fds->out_f = ft_lstnewfd(1);
	fds->app_f = ft_lstnewfd(1);
	fds->here_f = ft_lstnewfd(0);
	while (exenv.args)
	{
		if (exenv.args && exenv.args->type == HEREDOC)
			ft_fdadd_back(&fds->here_f,
				ft_lstnewfd(ft_document(exenv.env, exenv.args)));
		else if (exenv.args && exenv.args->type == OUT)
			ft_fdadd_back(&fds->out_f, ft_lstnewfd(ft_openout(exenv.args)));
		else if (exenv.args && exenv.args->type == APPEND)
			ft_fdadd_back(&fds->app_f, ft_lstnewfd(ft_append(exenv.args)));
		else if (exenv.args && exenv.args->type == IN)
			ft_fdadd_back(&fds->in_f, ft_lstnewfd(ft_openin(exenv.args)));
		exenv.args = exenv.args->next;
	}
}
