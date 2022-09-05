/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:57:52 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/05 19:02:16 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fds(t_fds **fds)
{
	(*fds)->in_f = ft_lstnewfd(0);
	(*fds)->out_f = ft_lstnewfd(1);
	(*fds)->app_f = ft_lstnewfd(1);
	(*fds)->here_f = ft_lstnewfd(0);
}

int	ft_openout(t_args *nw)
{
	int	out;

	out = open(*(nw->arg), O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (out == -1)
		perror(*(nw->arg));
	return (out);
}

int	ft_openin(t_args *nw)
{
	int	in;

	in = open(*(nw->arg), O_RDONLY, 0777);
	if (in == -1)
		perror(*(nw->arg));
	return (in);
}

int	ft_append(t_args *nw)
{
	int	ap;

	ap = open(*(nw->arg), O_APPEND | O_CREAT | O_RDWR, 0777);
	if (ap == -1)
		perror(*(nw->arg));
	return (ap);
}
