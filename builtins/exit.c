/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:51:49 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/05 22:26:01 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
