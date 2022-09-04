/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:16:17 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/04 15:07:16 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_exenv exenv)
{
	while (exenv.env)
	{
		if (exenv.env->key)
			printf("%s=\"%s\"\n", exenv.env->key, exenv.env->value);
		exenv.env = exenv.env->next;
	}
}
