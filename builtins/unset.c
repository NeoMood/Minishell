/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 00:57:58 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/04 15:20:47 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_env(char *var, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, var))
		{
			env->key = NULL;
			break ;
		}
		env = env->next;
	}
}

void	del_exp(char *var, t_exp *exp)
{
	while (exp)
	{
		if (!ft_strcmp(exp->key, var))
		{
			exp->key = NULL;
			break ;
		}
		exp = exp->next;
	}
}

void	ft_unset(t_exenv exenv)
{
	int	i;

	i = 1;
	if (exenv.args->arg[1])
	{
		while (exenv.args->arg[i])
		{
			if (check_key(exenv.args->arg[i]))
			{
				printf("unset: `%s': not a valid identifier\n",
					exenv.args->arg[i]);
				mode.g_exit = 1;
				return ;
			}
			del_env(exenv.args->arg[i], exenv.env);
			del_exp(exenv.args->arg[i], exenv.exp);
			i++;
		}
	}
}
