/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 00:57:58 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/24 22:09:07 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_env(char *var, t_env *env)
{
	while(env)
	{
		if(!ft_strcmp(env->key, var))
		{
			env->key = NULL;
			break;
		}
		env = env->next;
	}
}

void	del_exp(char *var, t_exp *exp)
{
	while(exp)
	{
		if(!ft_strcmp(exp->key, var))
		{
			exp->key = NULL;
			break;
		}
		exp = exp->next;
	}
}

void    ft_unset(t_args *line, t_exenv exenv)
{
	int i;

	i = 1;
	if(line->arg[1])
	{
		while(line->arg[i])
		{
			del_env(line->arg[i], exenv.env);
			del_exp(line->arg[i], exenv.exp);
			i++;
		}
	}
}