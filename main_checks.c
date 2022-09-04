/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:53:55 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/04 22:54:25 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	out_check(t_fds	**fds)
{
	(*fds)->new_out = (*fds)->out_f->next->fd;
	if ((*fds)->out_f->next)
		(*fds)->out_f = (*fds)->out_f->next;
}

int	check_redirections2(t_exenv *exenv, t_fds	**fds)
{
	if (exenv->args->type == OUT)
		out_check(fds);
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
	else
		return (-1);
	return (0);
}

void	check_redirections(t_exenv *exenv, t_fds	**fds)
{
	while (exenv->args)
	{
		if (check_redirections2(exenv, fds) == -1)
			break ;
		exenv->args = exenv->args->next;
	}
}

void	check_command(t_exenv *exenv, t_fds	**fds)
{
	if (exenv->args != NULL && exenv->args->type == COMMAND)
	{
		if ((*fds)->new_out != 1)
		{
			dup2((*fds)->new_out, STDOUT_FILENO);
			close((*fds)->new_out);
		}
		if ((*fds)->new_in != 0)
		{
			dup2((*fds)->new_in, STDIN_FILENO);
			close((*fds)->new_in);
		}
		if (!ft_check_builtins(*exenv))
			ft_builtins((*exenv), (*fds));
		else
			parse_cmd((*exenv));
	}
}
