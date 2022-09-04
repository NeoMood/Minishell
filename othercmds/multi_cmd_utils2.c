/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:35:18 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/04 22:38:10 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	list_size(t_env	*env)
{
	t_env	*clone;
	int		i;

	clone = env;
	i = 0;
	while (clone)
	{
		i++;
		clone = clone->next;
	}
	return (i);
}

void	get_filerror(char **cmd)
{
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
