/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 00:57:58 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/22 14:54:08 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_env(t_args *line, t_env *env)
{
	while(env)
	{
		if(!ft_strcmp(env->key, line->arg[1]))
		{
			env->key = NULL;
			break;
		}
		env = env->next;
	}
}

void	del_exp(t_args *line, t_exp *exp)
{
	while(exp)
	{
		if(!ft_strcmp(exp->key, line->arg[1]))
		{
			exp->key = NULL;
			break;
		}
		exp = exp->next;
	}
}

void    ft_unset(t_args *line, t_env *env, t_exp *exp)
{
	(void)exp;
	if(line->arg[1])
	{
		del_env(line, env);
		del_exp(line, exp);
		// while(env)
		// {
		// 	if(!ft_strcmp(env->key, line->arg[1]))
		// 	{
		// 		env->key = NULL;
		// 		break;
		// 	}
		// 	env = env->next;
		// }
	}
}