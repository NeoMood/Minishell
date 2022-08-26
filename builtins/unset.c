/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 00:57:58 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/26 01:55:30 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_env(char *var, t_env *env, t_env	*head)
{
	while(env)
	{
		if(!ft_strcmp(env->key, var))
		{
			if (!ft_strcmp(env->key, head->key))
			{
				puts("hna");
				env = env->next;
			}
			else
				env->key = NULL;
			break;
		}
		env = env->next;
	}
}

void	del_exp(char *var, t_exp *exp, t_env	*head)
{
	while(exp)
	{
		if(!ft_strcmp(exp->key, var))
		{
			if (!ft_strcmp(exp->key, head->key))
				exp = exp->next;
			else
				exp->key = NULL;
			break;
		}
		exp = exp->next;
	}
}

void    ft_unset(t_exenv exenv)
{
	int i;

	i = 1;
	exenv.head = exenv.env;
	if(exenv.args->arg[1])
	{
		while(exenv.args->arg[i])
		{
			del_env(exenv.args->arg[i], exenv.env, exenv.head);
			del_exp(exenv.args->arg[i], exenv.exp, exenv.head);
			i++;
		}
	}
}