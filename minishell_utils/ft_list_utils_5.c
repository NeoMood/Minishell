/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 23:02:42 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/04 23:03:50 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_addbacknode(t_env **env, t_env *nv)
{
	if (*env)
		ft_last_node(*env)->next = nv;
	else
		*env = nv;
}

void	ft_addbacknode2(t_exp **exp, t_exp *nv)
{
	if (*exp)
		ft_last_node2(*exp)->next = nv;
	else
		*exp = nv;
}

void	printenv(t_env *ev)
{
	while (ev)
	{
		printf("%s %s\n", ev->key, ev->value);
		ev = ev->next;
	}
}
