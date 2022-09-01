/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sighandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:29:40 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/01 19:51:30 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		write (1, "\n", 2);
		rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
		rl_catch_signals = 1;
	}
}

// void	ft_signalmodes(t_args *lst)
// {
// 	if (mode.g_sig == 1 && lst->type == HEREDOC)
// 	{
// 		puts("ok");
// 		signal(SIGINT, ft_handler);
// 	}
// 	if (mode.g_sig == 0)
// 		signal(SIGINT, ft_handler);
// }