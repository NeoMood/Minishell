/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:51:49 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/04 21:32:22 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_error(t_exenv exenv)
{
	write (1, "exit\n", 5);
	printf ("Minishell: exit: %s: numeric argument required\n",
		exenv.args->arg[1]);
	exit (1);
}

static void	ft_handlelong(t_exenv exenv)
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

static void	ft_negativenum(int j, t_exenv exenv)
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

static void	ft_postifnum(int j, t_exenv exenv)
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

static void	ft_norm(void)
{
	write (1, "exit\n", 5);
	g_mode.g_exit = 0;
	exit (0);
}

int	ft_exit(t_exenv exenv)
{
	int	i;
	int	j;

	i = 0;
	if (exenv.args->arg[1] && !exenv.args->arg[2])
	{
		while (exenv.args->arg[1][i])
		{
			j = 0;
			if (exenv.args->arg[1][j] == '-')
				ft_negativenum(j, exenv);
			else
				ft_postifnum(j, exenv);
			i++;
		}
	}
	else if (exenv.args->arg[1] && exenv.args->arg[1])
	{
		printf("exit\n");
		printf ("Minishell: exit: too many arguments\n");
		g_mode.g_exit = 127;
	}
	else
		ft_norm();
	return (0);
}
