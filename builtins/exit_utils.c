/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:56:16 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/04 22:59:08 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(t_exenv exenv)
{
	write (1, "exit\n", 5);
	printf ("Minishell: exit: %s: numeric argument required\n",
		exenv.args->arg[1]);
	exit (1);
}

void	ft_handlelong(t_exenv exenv)
{
	int	j;

	j = 0;
	while (exenv.args->arg[1][j])
	{
		if (!ft_strcmp(exenv.args->arg[1], "9223372036854775807"))
		{
			write (1, "exit\n", 5);
			g_mode.g_exit = 255;
			exit (255);
		}
		else
		{
			g_mode.g_exit = 255;
			ft_error(exenv);
		}
		j++;
	}
}

void	ft_negativenum(int j, t_exenv exenv)
{
	int	l;

	l = 0;
	if (exenv.args->arg[1][j] == '-')
	{
		l = j;
		while (exenv.args->arg[1][l])
		{
			l++;
			if (ft_isdigit(exenv.args->arg[1][l]))
			{
				write (1, "exit\n", 5);
				g_mode.g_exit = 256 + ft_atoi(exenv.args->arg[1]) % 256;
				exit (213);
			}
			else
				ft_error(exenv);
			l++;
		}
	}
}

void	ft_postifnum(int j, t_exenv exenv)
{
	int	len;
	int	l;

	l = j;
	len = ft_strlen(exenv.args->arg[1]);
	if (len < 19)
	{
		if (ft_isdigit(exenv.args->arg[1][l]))
		{
			write (1, "exit\n", 5);
			g_mode.g_exit = ft_atoi(&exenv.args->arg[1][l]) % 256;
			exit (ft_atoi(&exenv.args->arg[1][l]) % 256);
		}
		else
			ft_error(exenv);
	}
	else
		ft_handlelong(exenv);
}
