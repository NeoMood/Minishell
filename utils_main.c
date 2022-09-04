/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:13:36 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/04 16:28:42 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_exit(void)
{
	rl_on_new_line();
	rl_redisplay();
	printf("exit\n");
	exit (1);
}

t_args	*ft_corrector(t_args *parse)
{
	parse = ft_merge(parse);
	parse = ft_joiner(parse);
	return (parse);
}

int	check_pipe(t_args *args)
{
	while (args)
	{
		if (args->type == PIPE)
			return (0);
		args = args->next;
	}
	return (1);
}

int	ft_check_builtins(t_exenv exenv)
{
	if (!ft_strcmp(exenv.args->arg[0], "cd"))
		return (0);
	else if (!ft_strcmp(exenv.args->arg[0], "pwd"))
		return (0);
	else if (!ft_strcmp(exenv.args->arg[0], "env"))
		return (0);
	else if (!ft_strcmp(exenv.args->arg[0], "echo"))
		return (0);
	else if (!ft_strcmp(exenv.args->arg[0], "export"))
		return (0);
	else if (!ft_strcmp(exenv.args->arg[0], "unset"))
		return (0);
	else if (!ft_strcmp(exenv.args->arg[0], "exit"))
		return (0);
	return (1);
}
