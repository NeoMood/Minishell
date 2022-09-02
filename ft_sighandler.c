/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sighandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:29:40 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/02 22:11:32 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <sys/signal.h>

void	ft_handlermodes(char *str)
{
	if (!ft_strcmp(str, "Minishell"))
	{
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (!ft_strcmp(str, "heredoc"))
	{
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, SIG_IGN);
	}	
}

void	ft_handler(int sig)
{
	int	i;

	i = 0;
	if (sig == SIGINT && mode.g_sig == 0)
	{
		write (1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		rl_catch_signals = 1;
	}
	else if (sig == SIGINT && mode.g_sig == 2)
	{
		write(1, "\n", 1);
		exit(1);
	}
	else if (sig == SIGINT && mode.g_sig == 1)
		i++;
}
