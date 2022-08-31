/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:38:49 by yamzil            #+#    #+#             */
/*   Updated: 2022/08/31 17:06:03 by sgmira           ###   ########.fr       */
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
	// in = open(*(new->arg), O_TRUNC | O_CREAT | O_RDONLY, 0777);
    if (in == -1)
        perror(*(new->arg));
	return (in);
}

static int ft_append(t_args *new)
{
	int	ap;

	ap = open(*(new->arg), O_APPEND | O_CREAT | O_RDWR, 0777);
    if (ap == -1)
        perror(*(new->arg));
	return (ap);
}

t_file	*ft_lstlastfd(t_file *lst)
{
	if (!lst)
		return (NULL);
	if (lst -> next == NULL)
		return (lst);
	return (ft_lstlastfd(lst -> next));
}

t_file	*ft_lstnewfd(int fd)
{
	t_file	*new_fd;

	new_fd = (t_file *) malloc (sizeof (t_file));
	if (!new_fd)
		return (NULL);
	new_fd->fd = fd;
	new_fd->next = NULL;
	return (new_fd);
}

void	ft_fdadd_back(t_file **lst, t_file *new)
{
	t_file	*head;

	if (*lst)
	{
		head = *lst;
		head = ft_lstlastfd(head);
		head->next = new;
	}
	else
		(*lst) = new;
}

void    ft_redirection(t_fds    *fds, t_exenv exenv)
{
    fds->in_fd = 0;
	fds->out_f = ft_lstnewfd(1);
	fds->app_f = ft_lstnewfd(1);
    fds->heredoc_fd = 0;

    while (exenv.args)
    {
        if (exenv.args && exenv.args->type == HEREDOC)
            fds->heredoc_fd = ft_document(exenv.args);
        else if (exenv.args && exenv.args->type == OUT)
            ft_fdadd_back(&fds->out_f, ft_lstnewfd(ft_openout(exenv.args)));
        else if (exenv.args && exenv.args->type == APPEND)
            ft_fdadd_back(&fds->app_f, ft_lstnewfd(ft_append(exenv.args)));
        else if (exenv.args && exenv.args->type == IN)
            fds->in_fd = ft_openin(exenv.args);
        exenv.args = exenv.args->next;
    }
}