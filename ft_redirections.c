/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:38:49 by yamzil            #+#    #+#             */
/*   Updated: 2022/08/14 22:28:56 by yamzil           ###   ########.fr       */
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
		heredoc = readline("heredocument: "); // free here
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
    if (out == -1)
        perror(*(new->arg));
	return (out);
}

static int ft_openin(t_args *new)
{
	int	in;

	in = open(*(new->arg), O_TRUNC | O_CREAT | O_RDONLY, 0777);
    if (in == -1)
        perror(*(new->arg));
	return (in);
}

static int ft_append(t_args *new)
{
	int	in;

	in = open(*(new->arg), O_APPEND | O_CREAT | O_RDONLY, 0777);
    if (in == -1)
        perror(*(new->arg));
	return (in);
}

void    ft_redirection(t_args *parse)
{
    int heredoc_fd;
    int redirectioninput_fd;
    int redirectionoutput_fd;
    int append_fd;
    while (parse)
    {
        if (parse && parse->type == HEREDOC)
            heredoc_fd = ft_document(parse);
        else if (parse && parse->type == OUT)
            redirectionoutput_fd = ft_openout(parse);
        else if (parse && parse->type == IN)
            redirectioninput_fd = ft_openin(parse);
        else if (parse && parse->type == APPEND)
            append_fd = ft_append(parse);
        parse = parse->next;
    }
}