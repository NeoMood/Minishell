/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sighandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:29:40 by yamzil            #+#    #+#             */
/*   Updated: 2022/08/09 21:03:04 by yamzil           ###   ########.fr       */
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
