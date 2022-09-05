/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sighandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:29:40 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/05 18:28:46 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <sys/signal.h>

void	ft_handler(int sig)
{
	int	i;

	i = 0;
	if (sig == SIGINT && g_mode.g_sig == 0)
	{
		write (1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_mode.g_exit = 130;
	}
	else if (sig == SIGINT && g_mode.g_sig == 2)
	{
		write(1, "\n", 1);
		exit(1);
	}
	else if (sig == SIGINT && g_mode.g_sig == 1)
		i++;
}

void	ft_hide_c(void)
{
	struct termios	att;

	tcgetattr(STDIN_FILENO, &att);
	att.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &att);
}

void	show_ctrl(void)
{
	struct termios	att;

	tcgetattr(STDIN_FILENO, &att);
	att.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &att);
}
