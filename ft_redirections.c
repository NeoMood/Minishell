/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:38:49 by yamzil            #+#    #+#             */
/*   Updated: 2022/08/26 17:13:18 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_document(t_args *here)
{
	char *heredoc;
    char *s;
    int fd;

    fd = open("tmpfile", O_TRUNC | O_CREAT | O_RDWR, 0777);
    if (fd < 0)
        return (0);
	while (1)
	{
		heredoc = readline("> "); // free here
        // puts(heredoc);
		if (!heredoc) 
			return fd; 
		if (!ft_strcmp(heredoc, *here->arg))
			break ;
		ft_putstr_fd(heredoc, fd);
        ft_putstr_fd("\n", fd);
        s = ft_strjoin(s, heredoc);
        s = ft_strjoin(s, "\n");
	}
    printf("%s\n", s);
	return (fd);
}

static int ft_openout(t_args *new)
{
	int	out;
    // int tmp;
    // char buff[10000];

	out = open(*(new->arg), O_TRUNC | O_CREAT | O_WRONLY, 0777);
    if (out == -1)
        perror(*(new->arg));

    // tmp = ft_document(new);
    // read(tmp, buff, 1000);
    // ft_putstr_fd(buff, out);
	return (out);
}

// static int ft_openin(t_args *new)
// {
// 	int	in;

// 	in = open(*(new->arg), O_TRUNC | O_CREAT | O_RDONLY, 0777);
//     if (in == -1)
//         perror(*(new->arg));
// 	return (in);
// }

static int ft_append(t_args *new)
{
	int	in;

	in = open(*(new->arg), O_APPEND | O_CREAT | O_RDONLY, 0777);
    if (in == -1)
        perror(*(new->arg));
	return (in);
}

// void    ft_redirection(t_args *parse)
void    ft_redirection(t_exenv exenv)
{
    int heredoc_fd;
    // int redirectioninput_fd;
    // int redirectionoutput_fd;
    // int append_fd;
    while (exenv.args)
    {
        if (exenv.args && exenv.args->type == HEREDOC)
            heredoc_fd = ft_document(exenv.args);
        else if (exenv.args && exenv.args->type == OUT)
            exenv.out_fd = ft_openout(exenv.args);
        else if (exenv.args && exenv.args->type == APPEND)
            exenv.in_fd = ft_append(exenv.args);
        exenv.args = exenv.args->next;
    }
}