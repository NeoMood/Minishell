/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:38:49 by yamzil            #+#    #+#             */
/*   Updated: 2022/08/26 21:33:00 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_document(t_args *here)
{
	char *heredoc;
    int fd;

    fd = open("tmpfile", O_TRUNC | O_CREAT | O_RDWR, 0777);
    if (fd < 0)
        return (0);
	while (1)
	{
		heredoc = readline("> "); // free here

		if (!heredoc) 
			return fd; 
		if (!ft_strcmp(heredoc, *here->arg))
			break ;
		ft_putstr_fd(heredoc, fd);
        ft_putstr_fd("\n", fd);
	}
	return (fd);
}

static int ft_openout(t_args *new)
{
	int	out;

	out = open(*(new->arg), O_TRUNC | O_CREAT | O_WRONLY, 0777);
    // out = open(*(new->arg), O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (out == -1)
        perror(*(new->arg));
	return (out);
}

static int ft_openin(t_args *new)
{
	int	in;

	in = open(*(new->arg), O_TRUNC | O_CREAT | O_RDWR, 0777);
    if (in == -1)
        perror(*(new->arg));
	return (in);
}

// static int ft_append(t_args *new)
// {
// 	int	in;

// 	in = open(*(new->arg), O_APPEND | O_CREAT | O_RDONLY, 0777);
//     if (in == -1)
//         perror(*(new->arg));
// 	return (in);
// }

void    ft_redirection(t_fds    *fds, t_exenv exenv)
{
    while (exenv.args)
    {
        if (exenv.args && exenv.args->type == HEREDOC)
            fds->heredoc_fd = ft_document(exenv.args);
        else if (exenv.args && exenv.args->type == OUT)
            fds->out_fd = ft_openout(exenv.args);
        // else if (exenv->args && exenv->args->type == APPEND)
        //     exenv->in_fd = ft_append(exenv->args);
        else if (exenv.args && exenv.args->type == IN)
            fds->in_fd = ft_openin(exenv.args);
        exenv.args = exenv.args->next;
    }
}