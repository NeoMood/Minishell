/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 00:57:58 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/22 01:30:50 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	del_env()
// {
	
// }

// void	del_exp()
// {
	
// }

void    ft_unset(t_args *line, t_env *env)
{
	if(line->arg[1])
	{
		while(env)
		{
			if(!ft_strcmp(env->key, line->arg[1]))
			{
				env->key = NULL;
			}
			env = env->next;
		}
	}
}